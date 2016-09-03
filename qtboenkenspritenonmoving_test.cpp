#include "qtboenkenspritenonmoving_test.h"

#include "qtboenkenspritenonmoving.h"
#include "qtboenkenspriteplayer.h"
#include "qtboenkensprite.h"

void ribi::bnkn::qtboenkenspritenonmoving_test::all_tests()
{
  const double obstacle_x = 160.0;
  const double obstacle_y = 100.0;
  const SpriteNonMoving obstacle(
    obstacle_x, //x
    obstacle_y, //y
    32   //size
  );
  SpritePlayer player(
    obstacle_x, //x
    obstacle_y, //y
    0.0, //angle
    32,  //size
    255, //r
    255, //g
    255  //b
  );
  // Player below obstacle, moves up
  {
    player.SetX(obstacle_x);
    player.SetY(obstacle_y + 30.0);
    player.SetSpeed(0.0,-4.0);
    assert(player.GetDeltaY() < -3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaY() > 1.0 && "Be gentle, due to friction");
  }
  // Player right of obstacle, moves left
  {
    player.SetX(obstacle_x + 30.0);
    player.SetY(obstacle_y + 0.0);
    player.SetSpeed(-4.0,0.0);
    assert(player.GetDeltaX() < -3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaX() > 1.0 && "Be gentle, due to friction");
  }

  // Player above obstacle, moves down
  {
    player.SetX(obstacle_x + 0.0);
    player.SetY(obstacle_y - 30.0);
    player.SetSpeed(0.0,4.0);
    assert(player.GetDeltaY() > 3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaY() < -1.0 && "Be gentle, due to friction");
  }
  // Player left of obstacle, moves right
  {
    player.SetX(obstacle_x - 30.0);
    player.SetY(obstacle_y + 0.0);
    player.SetSpeed(4.0,0.0);
    assert(player.GetDeltaX() >  3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaX() < -1.0 && "Be gentle, due to friction");
  }
}
