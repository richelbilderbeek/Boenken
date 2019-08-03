#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtboenkensprite.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <QBitmap>
#include <QImage>
#include <QPainter>
#include <QPixmap>

#include "geometry.h"
#pragma GCC diagnostic pop

///The maximum x coordinat a Sprite can have
int ribi::bnkn::Sprite::m_maxx = 320;

///The maximum y coordinat a Sprite can have
int ribi::bnkn::Sprite::m_maxy = 200;

ribi::bnkn::Sprite::Sprite(
  const double x,
  const double y,
  const int size,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
  : m_x(x),
    m_y(y),
    m_pixmap(DrawGlobe(size,size,r,g,b)),
    m_size(size)
{
}

QRect ribi::bnkn::Sprite::rect() const
{
  return QRect(m_x,m_y,m_size,m_size);
}

const QPixmap& ribi::bnkn::Sprite::pixmap() const noexcept
{
  return m_pixmap;
}

void ribi::bnkn::Sprite::Draw(QPainter& painter) const
{
  painter.drawPixmap(this->rect(),this->pixmap());
}

std::string ribi::bnkn::Sprite::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::bnkn::Sprite::GetVersionHistory() noexcept
{
  return
  {
    "2010-xx-xx: version 1.0: initial version",
    "2013-04-30: added testing, fixed bug in GetAngle"
  };
}

bool ribi::bnkn::IsCollision(const Sprite& p1, const Sprite& p2) noexcept
{
  const double dx = p2.getX() - p1.getX();
  const double dy = p2.getY() - p1.getY();
  const double distance = std::sqrt((dy * dy) + (dx * dx));
  const double collision_distance
    = boost::numeric_cast<double>(p1.GetSize() + p2.GetSize()) / 2.0;
  return distance < collision_distance;
}

void ribi::bnkn::Sprite::setArenaSize(const int width, const int height)
{
  m_maxx = width;
  m_maxy = height;
}

//From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
QPixmap ribi::bnkn::Sprite::DrawGlobe(
  const int width,
  const int height,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
{
  QPixmap pixmap(width,height);
  QImage image = pixmap.toImage();
  assert(width != 0);
  assert(image.bytesPerLine() / width == 4
    && "Assume there are 4 bytes per pixel");

  const double r_max = boost::numeric_cast<double>(r);
  const double g_max = boost::numeric_cast<double>(g);
  const double b_max = boost::numeric_cast<double>(b);
  const double midX = boost::numeric_cast<double>(width ) / 2.0;
  const double midY = boost::numeric_cast<double>(height) / 2.0;
  const double max_dist = std::min(midX,midY);

  for (int y=0; y!=height; ++y)
  {

    unsigned char * const line
      = static_cast<unsigned char *>(image.scanLine(y));
    const double y_d = boost::numeric_cast<double>(y);
    for (int x=0; x!=width; ++x)
    {
      const double x_d = boost::numeric_cast<double>(x);
      const double dist
        = std::sqrt(
            ((x_d - midX) * (x_d - midX))
          + ((y_d - midY) * (y_d - midY)) );
      if (dist <= max_dist)
      {
        const double rel_dist = dist / max_dist;
        const int r_here = rel_dist * r_max;
        const int g_here = rel_dist * g_max;
        const int b_here = rel_dist * b_max;
        assert(r_here >= 0);
        assert(r_here < 256);
        assert(g_here >= 0);
        assert(g_here < 256);
        assert(b_here >= 0);
        assert(b_here < 256);
        line[x*4+3] = 255; //Alpha value
        line[x*4+2] = r_here; //Red
        line[x*4+1] = g_here; //Green
        line[x*4+0] = b_here; //Blue
      }
      else
      {
        line[x*4+3] = 0; //Alpha value
        line[x*4+2] = 0; //Red
        line[x*4+1] = 0; //Green
        line[x*4+0] = 0; //Blue
      }
    }
  }
  pixmap = pixmap.fromImage(image);

  //Add transparency
  const QBitmap mask = pixmap.createMaskFromColor(QColor(0,0,0,0).rgb());
  pixmap.setMask(mask);

  return pixmap;
}

//double ribi::bnkn::Sprite::GetAngle(const double dx, const double dy) noexcept
//{
//  return Geometry().GetAngleClockScreen(dx,dy);
//}

//From http://www.richelbilderbeek.nl/CppDoPerfectElasticCollision.htm
void ribi::bnkn::DoPerfectElasticCollision(
  const double angleCollision,
  double& angle1,
  double& speed1,
  double& angle2,
  double& speed2) noexcept
{
  const double pi{boost::math::constants::pi<double>()};
  //The length of the impulse of player 1 (assumes both players have equal mass!)
  const double A{speed1};
  //The length of the impulse of player 2 (assumes both players have equal mass!)
  const double E{speed2};
  //The angles between the two globes
  const double c{angleCollision};
  //The angle between c and the impulse direction of player 1
  const double a{c - angle1};
  //The angle between c and the impulse direction of player 2
  const double b{c + pi - angle2};

  //Seperate the impulses to their impulses paralel and othoganal the angle of collision
  //The length of the impulse of player 1 parallel to the collision
  const double B{A * std::cos(a)};
  //The length of the impulse of player 1 orthogonal to the collision
  const double C{A * std::sin(a)};
  //The length of the impulse of player 2 parallel to the collision
  const double F{E * std::cos(b)};
  //The length of the impulse of player 2 orthogonal to the collision
  const double G{E * std::sin(b)};

  //Seperate the impulses in X and Y directions
  const double BdX{B *  std::sin(c + (0.0 * pi))};
  const double BdY{B * -std::cos(c + (0.0 * pi))};
  const double CdX{C *  std::sin(c + (1.5 * pi))};
  const double CdY{C * -std::cos(c + (1.5 * pi))};
  const double FdX{F *  std::sin(c + (1.0 * pi))};
  const double FdY{F * -std::cos(c + (1.0 * pi))};
  const double GdX{G *  std::sin(c + (0.5 * pi))};
  const double GdY{G * -std::cos(c + (0.5 * pi))};

  //The resulting impulses
  //The resulting impulse of player 1 in the X direction
  const double DdX{CdX + FdX};
  //The resulting impulse of player 1 in the Y direction
  const double DdY{CdY + FdY};
  //The resulting impulse of player 2 in the X direction
  const double HdX{BdX + GdX};
  //The resulting impulse of player 2 in the Y direction
  const double HdY{BdY + GdY};

  //Write the final results
  angle1 = Geometry().GetAngleClockScreen(DdX, DdY);
  angle2 = Geometry().GetAngleClockScreen(HdX, HdY);
  speed1 = std::sqrt( (DdX * DdX) + (DdY * DdY) ); //Pythagoras
  speed2 = std::sqrt( (HdX * HdX) + (HdY * HdY) ); //Pythagoras
}
