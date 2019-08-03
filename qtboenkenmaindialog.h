#ifndef QTBOENKENMAINDIALOG_H
#define QTBOENKENMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push

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
  Q_OBJECT //!OCLINT

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

private slots:
  void onTimer();
  void onCountdownTimer();
};

///Paint paints a Pixmap to a single color fast,
///from http://www.richelbilderbeek.nl/CppPaint.htm
void Paint(
  QPixmap& pixmap,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b,
  const unsigned char a = 255
);

} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENMAINDIALOG_H
