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
#ifndef QTBOENKENARENADIALOG_H
#define QTBOENKENARENADIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#include "boenkenarenasettings.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenArenaDialog;
}

namespace ribi {
namespace bnkn {

///QtBoenkenArenaDialog
///
///Dialog to setup up the arena
class QtArenaDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtArenaDialog(QWidget *parent = 0) noexcept;
  QtArenaDialog(const QtArenaDialog&) = delete;
  QtArenaDialog& operator=(const QtArenaDialog&) = delete;
  ~QtArenaDialog() noexcept;

  std::pair<int,int> GetScreenSize() const noexcept;
  int GetNballs() const noexcept;
  int GetNobstacles() const noexcept;
  Formation GetFormation() const noexcept;
  double GetFriction() const noexcept;
  ArenaSettings GetSettings() const noexcept;

private:
  Ui::QtBoenkenArenaDialog *ui;
};

} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENARENADIALOG_H
