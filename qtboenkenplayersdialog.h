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
#ifndef QTBOENKENPLAYERSDIALOG_H
#define QTBOENKENPLAYERSDIALOG_H



#include "qthideandshowdialog.h"


namespace Ui {
  class QtBoenkenPlayersDialog;
}

namespace ribi {
namespace bnkn {

///Dialog to connect sprites to their controllers\n
///A controller can be\n
///- a human\n
///- a computer\n
class QtPlayersDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtPlayersDialog(QWidget *parent = 0);
  QtPlayersDialog(const QtPlayersDialog&) = delete;
  QtPlayersDialog& operator=(const QtPlayersDialog&) = delete;
  ~QtPlayersDialog() noexcept;

private:
  Ui::QtBoenkenPlayersDialog *ui;
};

} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENPLAYERSDIALOG_H
