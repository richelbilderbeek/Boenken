//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2016 Richel Bilderbeek

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
#ifndef QTBOENKENMENUDIALOG_H
#define QTBOENKENMENUDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenMenuDialog;
}

namespace ribi {
namespace bnkn {


struct ArenaSettings;
struct SpriteBall;
struct SpriteNonMoving;
struct SpritePlayer;
struct QtPlayersDialog;
struct QtArenaDialog;
struct QtControlsDialog;

///QtBoenkenMenuDialog
///
///Gathers all options to start a game
class QtMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMenuDialog(QWidget *parent = 0);
  QtMenuDialog(const QtMenuDialog&) = delete;
  QtMenuDialog& operator=(const QtMenuDialog&) = delete;
  ~QtMenuDialog() noexcept;

private:
  Ui::QtBoenkenMenuDialog *ui;
  QtControlsDialog * const m_controls;
  QtPlayersDialog * const m_players;
  QtArenaDialog * const m_arena;

  static std::vector<SpritePlayer> CreatePlayers(const ArenaSettings& a);
  static std::vector<SpriteBall> CreateBalls(const ArenaSettings& a);
  static std::vector<SpriteNonMoving> CreateObstacles(const ArenaSettings& a);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void onControlsClick();
  void onPlayersClick();
  void onArenaClick();
  void onStartClick();
  void onAboutClick();
};

} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENMENUDIALOG_H
