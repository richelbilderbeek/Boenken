


#include "qtboenkenspriteplayer.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <QPainter>

#include "geometry.h"


constexpr double ribi::bnkn::GetAcceleration()
{
  return 1.0;
}
constexpr double ribi::bnkn::GetTurnSpeed()
{
  return boost::math::constants::pi<double>() / 10.0;
}

///The number of SpritePlayers.
///for debugging purposes
//int ribi::bnkn::SpritePlayer::ms_n_players = 0;

ribi::bnkn::SpritePlayer::SpritePlayer(
  const double x,
  const double y,
  const double angle,
  const int size,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b
) : SpriteMoving(x,y,size,r,g,b),
    m_angle(angle)
    //m_id(ms_n_players)

{
  //++ms_n_players;
  //std::clog << "The " << ms_n_players
  //  << "th player is created at ("
  //  << this->getX() << ","
  //  << this->getY() << ")\n";
}

ribi::bnkn::SpritePlayer::~SpritePlayer() noexcept
{
  //std::clog << "The " << ms_n_players
  //  << "th player is destroyed\n";
  //--ms_n_players;
  //assert(ms_n_players >= 0);
}

void ribi::bnkn::SpritePlayer::Move() noexcept
{
  ///Move the sprite
  m_x += m_dx;
  m_y += m_dy;

  ///Calculate the sprites maximal coordinats
  const double maxx = this->m_maxx - this->GetSize();
  const double maxy = this->m_maxy - this->GetSize();
  assert(maxx > 0);
  assert(maxy > 0);

  ///Move moving sprite into the arena
  if (m_x <  0.0)
  {
    m_x =  0.0; m_dx =  std::fabs(m_dx);
    //std::clog << "Player #" << m_id << " moved to right to ("
    //  << m_x << "," << m_y << ")\n";
  }
  if (m_y <  0.0)
  {
    m_y =  0.0; m_dy =  std::fabs(m_dy);
    //std::clog << "Player #" << m_id << " moved downwards to ("
    //  << m_x << "," << m_y << ")\n";
  }
  if (m_x > maxx)
  {
    m_x = maxx; m_dx = -std::fabs(m_dx);
    //std::clog << "Player #" << m_id << " moved to left to ("
    //  << m_x << "," << m_y << ")\n";
  }
  if (m_y > maxy)
  {
    m_y = maxy; m_dy = -std::fabs(m_dy);
    //std::clog << "Player #" << m_id << " moved upwards to ("
    //  << m_x << "," << m_y << ")\n";
  }

  ///Decrease the speed due to friction
  m_dx *= m_friction;
  m_dy *= m_friction;
}


void ribi::bnkn::SpritePlayer::Accelerate() noexcept
{
  m_dx += (std::sin(m_angle) * GetAcceleration());
  m_dy -= (std::cos(m_angle) * GetAcceleration());
}

void ribi::bnkn::SpritePlayer::SetSpeed(const double dx, const double dy) noexcept
{
  SpriteMoving::SetSpeed(dx,dy);

  //Don't set the angle of the player!
  //The angle is where the player 'looks to'
  //this->m_angle = Geometry().GetAngleClockScreen(dx,dy);
}

void ribi::bnkn::SpritePlayer::TurnRight() noexcept
{
  m_angle+=GetTurnSpeed();
}

void ribi::bnkn::SpritePlayer::Draw(QPainter& painter) const
{
  //Draw the globe and possibly impulse
  SpriteMoving::Draw(painter);
  //Determine the player center
  const double half_size = boost::numeric_cast<double>(GetSize()) / 2.0;
  const double x_mid = m_x + half_size;
  const double y_mid = m_y + half_size;
  //Draw the line the player looks at
  const double x2 = x_mid + (std::sin(m_angle) * half_size);
  const double y2 = y_mid - (std::cos(m_angle) * half_size);
  painter.drawLine(x_mid,y_mid,x2,y2);
}
