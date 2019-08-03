#ifndef BOENKENGAME_H
#define BOENKENGAME_H

#include <vector>




#include "boenkenarenasettings.h"
#include "qtboenkenspriteplayer.h"
#include "boenkencontrols.h"
#include "qtboenkensprite.h"
#include "qtboenkenspriteball.h"
#include "qtboenkenspritenonmoving.h"



struct QPainter;

namespace ribi {

namespace bnkn {

///Boenken contains the game.
///Boenken can be displayed by DialogMain
struct Game
{
  Game(
    const ArenaSettings& arena_settings,
    const Controls& controls,
    const std::vector<SpritePlayer>& players,
    const std::vector<SpriteBall>& balls,
    const std::vector<SpriteNonMoving>& obstacles
  );

  void drawPlayers(QPainter& painter) const;
  int getWidth() const noexcept;
  int getHeight() const noexcept;
  std::pair<int,int> GetScore() const noexcept;
  void pressKey(const int key);

  ///Moves all sprites
  void tick();

  private:
  std::vector<SpritePlayer> m_players;
  std::vector<SpriteBall> m_balls;
  std::vector<SpriteNonMoving> m_obstacles;
  const ArenaSettings m_arena_settings;
  const Controls m_controls;
  bool m_verbose;

};

///Collect all moving sprites
///'players' and 'balls' cannot be const: these will become (con-const) SpriteMoving*
std::vector<SpriteMoving*> CollectMovingSprites(
std::vector<SpritePlayer>& players,
std::vector<SpriteBall>& balls
) noexcept;

std::vector<const Sprite*> CollectSprites(
const std::vector<SpritePlayer>& players,
const std::vector<SpriteBall>& balls,
const std::vector<SpriteNonMoving>& obstacles
) noexcept;

} //~namespace bnkn
} //~namespace ribi

#endif // BOENKENGAME_H
