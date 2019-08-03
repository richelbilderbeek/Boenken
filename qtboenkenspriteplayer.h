#ifndef BOENKENSPRITEPLAYER_H
#define BOENKENSPRITEPLAYER_H



#include <boost/checked_delete.hpp>
#include "qtboenkenspritemoving.h"


namespace ribi {
namespace bnkn {

///SpritePlayer is a MovingSprite that can respond to input
///and can only be deleted by boost::checked_delete
struct SpritePlayer final : public SpriteMoving
{
  SpritePlayer(
    const double x,
    const double y,
    const double angle,
    const int size,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b
  );
  ~SpritePlayer();

  void Accelerate() noexcept;
  void Draw(QPainter& painter) const override;
  double GetAngle() const noexcept { return m_angle; }

  void Move() noexcept override;
  void SetSpeed(const double dx, const double dy) noexcept override;
  void TurnRight() noexcept;

  private:
  ///Direction the player looks to
  ///Angle following the clock (0 = 12 o'clock, 0.5*pi = 3 o'clock)
  ///Note: the actual moving is done by m_dx and m_dy
  double m_angle;

};

///The acceleration (i.e. change of impulse)
///if a player presses accelerate
constexpr double GetAcceleration();

///The speed of turning around
///if a player presses turn
constexpr double GetTurnSpeed();

} //~namespace bnkn
} //~namespace ribi

#endif // BOENKENSPRITEPLAYER_H
