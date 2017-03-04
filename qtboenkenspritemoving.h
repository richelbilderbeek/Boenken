#ifndef BOENKENSPRITEMOVING_H
#define BOENKENSPRITEMOVING_H

#include "qtboenkensprite.h"

namespace ribi {
namespace bnkn {

///SpriteMoving is an abstract base class
struct SpriteMoving: public Sprite
{
  SpriteMoving(
    const double x,
    const double y,
    const int size,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b
  );
  virtual ~SpriteMoving();

  double CalcImpulseAngle() const noexcept;
  double CalcImpulseSpeed() const noexcept;
  virtual void Draw(QPainter& painter) const override;
  double GetDeltaX() const noexcept { return m_dx; }
  double GetDeltaY() const noexcept { return m_dy; }
  virtual void Move() = 0;
  void Move(const double dx, const double dy) { m_dx += dx; m_dy += dy; }

  //void SetDeltaX(const double dx) noexcept { m_dx = dx; }
  //void SetDeltaY(const double dy) noexcept { m_dy = dy; }
  virtual void SetSpeed(const double dx, const double dy) noexcept { m_dx = dx; m_dy = dy; }

  static void SetFriction(const double friction);
  static void Collision(SpriteMoving * const p1, SpriteMoving * const p2);

  ///Debugging purposes
  static int CountMovingSprites() noexcept { return sm_n_moving_sprites; }

  protected:
  double m_dx;
  double m_dy;
  static double m_friction;
  static int sm_n_moving_sprites;
};

} //~namespace bnkn
} //~namespace ribi

#endif // BOENKENSPRITEMOVING_H
