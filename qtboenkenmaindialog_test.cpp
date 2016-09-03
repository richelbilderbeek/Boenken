#include "qtboenkenmaindialog_test.h"

#include "boenkenarenasettings.h"
#include "boenkencontrols.h"
#include "qtboenkenmaindialog.h"
#include "qtboenkenmenudialog.h"


void ribi::bnkn::qtboenkenmaindialog_test::all_tests()
{
  ArenaSettings a;
  a.formation = Formation::circle_inward;
  a.friction = 0.999;
  a.n_balls = 1;
  a.n_obstacles = 4;
  a.screen_size = std::make_pair(320,200);
  Controls c;
  const std::vector<SpritePlayer> players{CreatePlayers(a)};
  const std::vector<SpriteBall> balls = CreateBalls(a);
  const std::vector<SpriteNonMoving> obstacles = CreateObstacles(a);
  const Game b{a,c,players,balls,obstacles};
  QtMainDialog d{b};
  d.show();
}
