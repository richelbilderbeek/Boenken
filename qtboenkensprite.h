#ifndef BOENKENSPRITE_H
#define BOENKENSPRITE_H

#include <cassert>





#include <QPixmap>


namespace ribi {
namespace bnkn {

///Sprite is the ABC of anything that must be drawn on screen
struct Sprite
{
  explicit Sprite(
    const double x,
    const double y,
    const int size,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b
  );
  virtual ~Sprite() = default;

  ///The size (width==height) in pixels
  int GetSize() const noexcept { return m_size; }

  ///The globe part of the Sprite
  const QPixmap& GetPixmap() const noexcept { return m_pixmap; }

  double getX() const noexcept { return GetX(); }
  double getY() const noexcept { return GetY(); }
  double GetX() const noexcept { return m_x; }
  double GetY() const noexcept { return m_y; }

  ///The x,y,w,h of the sprite
  QRect rect() const;

  const QPixmap& pixmap() const noexcept;

  ///Every sprite must be drawn to the screen
  virtual void Draw(QPainter& painter) const;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Sets the arena size,
  ///that is Sprite::m_maxx and Sprite::m_maxy.
  ///SpriteBall::SetGoalPoles defines the vertical
  ///range of the goal posts
  ///Every sprite must be within the arena
  static void setArenaSize(const int width, const int height);

  void setX(const double x) noexcept { SetX(x); }
  void setY(const double y) noexcept { SetY(y); }
  void SetX(const double x) noexcept { m_x  = x; }
  void SetY(const double y) noexcept { m_y  = y; }

  protected:
  double m_x;
  double m_y;
  static int m_maxx;
  static int m_maxy;


  ///Draws a globe with a nice 3D effect\n
  ///From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
  static QPixmap DrawGlobe(
    const int width,
    const int height,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b
  );

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  //static double GetAngle(const double dx, const double dy) noexcept;

  private:

  ///The globe part of the Sprite
  QPixmap m_pixmap;

  ///The size (width==height) in pixels
  int m_size;
};

///DoPerfectElasticCollision calculates the impulses after a
///collision.
///From http://www.richelbilderbeek.nl/CppDoPerfectElasticCollision.htm
void DoPerfectElasticCollision(
  const double angleCollision,
  double& angle1,
  double& speed1,
  double& angle2,
  double& speed2
) noexcept;

bool IsCollision(const Sprite& p1, const Sprite& p2) noexcept;

} //~namespace bnkn
} //~namespace ribi

#endif // SPRITE_H
