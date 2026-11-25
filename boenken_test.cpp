// Tests for Boenken
//
// The tests play the game for a short while,
// so that the code coverage is measured.
// Run with: ./boenken_test
#include <QtTest>

#include "qtboenkenarenadialog.h"
#include "qtboenkencontrolsdialog.h"
#include "qtboenkengame.h"
#include "qtboenkenmaindialog.h"
#include "qtboenkenmenudialog.h"

using namespace ribi::bnkn;

class boenken_test : public QObject
{
  Q_OBJECT

private:

  Game create_game()
  {
    const QtArenaDialog arena;
    const QtControlsDialog controls;
    const ArenaSettings a{arena.GetSettings()};
    const Controls c{controls.GetControls()};
    return Game(a, c, CreatePlayers(a), CreateBalls(a), CreateObstacles(a));
  }

private slots:

  void version_is_known()
  {
    QVERIFY(!GetVersion().empty());
    QVERIFY(!GetVersionHistory().empty());
  }

  void menu_dialog_can_be_shown()
  {
    QtMenuDialog d;
    d.show();
    QVERIFY(QTest::qWaitForWindowExposed(&d));
  }

  void game_can_be_created()
  {
    const Game g{create_game()};
    Q_UNUSED(g);
  }

  void game_can_be_played()
  {
    QtMainDialog d(create_game());
    d.show();
    QVERIFY(QTest::qWaitForWindowExposed(&d));
    const std::vector<Qt::Key> keys = {
      Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down,
      Qt::Key_A, Qt::Key_D, Qt::Key_W, Qt::Key_S,
      Qt::Key_Space, Qt::Key_Return
    };
    for (int i = 0; i != 10; ++i)
    {
      for (const auto key: keys)
      {
        QTest::keyPress(&d, key);
        QTest::qWait(20);
        QTest::keyRelease(&d, key);
      }
    }
    QTest::qWait(1000);
    QVERIFY(d.isVisible());
  }
};

QTEST_MAIN(boenken_test)
#include "boenken_test.moc"
