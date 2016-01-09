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
#ifndef QTBOENKENMAINDIALOG_H
#define QTBOENKENMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtboenkengame.h"
#include "qthideandshowdialog.h"
#include <QPixmap>
#include <QTimer>
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenMainDialog;
}

namespace ribi {
namespace bnkn {

///QtBoenkenMainDialog displays Boenken and handles user events
class QtMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMainDialog(
    const Game& game,
    QWidget *parent = 0
  );
  QtMainDialog(const QtMainDialog&) = delete;
  QtMainDialog& operator=(const QtMainDialog&) = delete;
  ~QtMainDialog() noexcept;

protected:
  void paintEvent(QPaintEvent*);
  void keyPressEvent(QKeyEvent*);

private:
  //UI
  Ui::QtBoenkenMainDialog *ui;
  //Graphics
  QPixmap m_background;
  //Other Qthings
  ///The main game timer
  QTimer * const m_timer;
  ///The timer that does the countdown
  QTimer * const m_timer_countdown;
  //Other member variables
  Game m_game;
  bool m_verbose;

  ///Paint paints a Pixmap to a single color fast,
  ///from http://www.richelbilderbeek.nl/CppPaint.htm
  static void Paint(
    QPixmap& pixmap,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b,
    const unsigned char a = 255
  );

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void onTimer();
  void onCountdownTimer();

};

} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENMAINDIALOG_H
