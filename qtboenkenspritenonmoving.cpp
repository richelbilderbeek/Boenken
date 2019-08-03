


#include "qtboenkenspritenonmoving.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>
#include "geometry.h"
#include "qtboenkenspritemoving.h"
#include "qtboenkenspriteplayer.h"



ribi::bnkn::SpriteNonMoving::SpriteNonMoving(
  const double x,
  const double y,
  const int size,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
  : Sprite(x,y,size,r,g,b)
{

}

void ribi::bnkn::SpriteNonMoving::Collision(
  const SpriteNonMoving& obstacle, SpriteMoving& moving
)
{
  if (!IsCollision(obstacle,moving)) return;
  /*

    O     -
          |
          | dy (in this case > 0)
          |
        M -
    |---|
      dx (in this case > 0)
  */
  const double dx = moving.getX() - obstacle.getX();
  const double dy = moving.getY() - obstacle.getY();
  //const double collision_distance
  //  = boost::numeric_cast<double>(obstacle.m_size + moving.m_size) / 2.0;
  //Obtain the relative angle between the players

  /*

    O
     \
      \
       \
        M

  angle_players in this case 135 degrees

  */
  const double angle_players = Geometry().GetAngleClockScreen(dx,dy);

  //Obtain the moving sprite's current impulse
  double moving_angle = moving.CalcImpulseAngle();
  double moving_speed = moving.CalcImpulseSpeed();
  //Obstacles have opposite impulse
  const double pi = boost::math::constants::pi<double>();
  double obstacle_angle = moving_angle + pi;
  double obstancle_speed = moving_speed;
  //Obtain the new impulses
  DoPerfectElasticCollision(
    angle_players, obstacle_angle,obstancle_speed,moving_angle,moving_speed
  );
  //Set the player's new impulse
  const double dx2 =  std::sin(moving_angle) * moving_speed;
  const double dy2 = -std::cos(moving_angle) * moving_speed;
  moving.SetSpeed(dx2,dy2);
  //Let the player move again
  moving.Move();
}
