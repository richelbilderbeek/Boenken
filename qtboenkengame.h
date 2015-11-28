//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#ifndef BOENKENGAME_H
#define BOENKENGAME_H

#include <vector>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "boenkenarenasettings.h"
#include "qtboenkenspriteplayer.h"
#include "boenkencontrols.h"
#include "qtboenkensprite.h"
#include "qtboenkenspriteball.h"
#include "qtboenkenspritenonmoving.h"

#pragma GCC diagnostic pop

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
  void tick();

  private:
  std::vector<SpritePlayer> m_players;
  std::vector<SpriteBall> m_balls;
  std::vector<SpriteNonMoving> m_obstacles;
  const ArenaSettings m_arena_settings;
  const Controls m_controls;
  bool m_verbose;

  ///Collect all moving sprites
  ///'players' and 'balls' cannot be const: these will become (con-const) SpriteMoving*
  static std::vector<SpriteMoving*> CollectMovingSprites(
    std::vector<SpritePlayer>& players,
    std::vector<SpriteBall>& balls
  ) noexcept;

  static std::vector<const Sprite*> CollectSprites(
    const std::vector<SpritePlayer>& players,
    const std::vector<SpriteBall>& balls,
    const std::vector<SpriteNonMoving>& obstacles
  ) noexcept;

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

};

} //~namespace bnkn
} //~namespace ribi

#endif // BOENKENGAME_H
