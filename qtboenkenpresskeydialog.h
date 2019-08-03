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
#ifndef QTBOENKENPRESSKEYDIALOG_H
#define QTBOENKENPRESSKEYDIALOG_H



#include "qthideandshowdialog.h"


namespace Ui {
  class QtBoenkenPressKeyDialog;
}

namespace ribi {
namespace bnkn {

///QtBoenkenPressKeyDialog asks the user to press
///any key. The key pressed can be requested
///later, by DialogControls.
class QtPressKeyDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtPressKeyDialog(QWidget *parent = 0);
  QtPressKeyDialog(const QtPressKeyDialog&) = delete;
  QtPressKeyDialog& operator=(const QtPressKeyDialog&) = delete;
  ~QtPressKeyDialog() noexcept;
  int GetKey() const noexcept { return m_key; }

protected:
  void keyPressEvent(QKeyEvent * e);

private:
  Ui::QtBoenkenPressKeyDialog *ui;
  int m_key;
};

} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENPRESSKEYDIALOG_H
