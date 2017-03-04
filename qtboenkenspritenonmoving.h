#ifndef BOENKENSPRITENONMOVING_H
#define BOENKENSPRITENONMOVING_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/checked_delete.hpp>
#include "qtboenkensprite.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace bnkn {

struct SpriteMoving;

///SpriteNonMoving are obstacles.
///Obstacles are grey per default
struct SpriteNonMoving final : public Sprite
{
  explicit SpriteNonMoving(
    const double x,
    const double y,
    const int size = 32,
    const unsigned char r = 255,
    const unsigned char g = 255,
    const unsigned char b = 255
  );

  public:
  void setX(const double x) { m_x = x; }
  void setY(const double y) { m_y = y; }

  ///A non-moving sprite, like an object, will not change
  static void Collision(const SpriteNonMoving& p1, SpriteMoving& p2);
};

} //~namespace bnkn
} //~namespace ribi

#endif // BOENKENSPRITENONMOVING_H
