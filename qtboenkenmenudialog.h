#ifndef QTBOENKENMENUDIALOG_H
#define QTBOENKENMENUDIALOG_H

#include <vector>



#include "qthideandshowdialog.h"


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
  Q_OBJECT //!OCLINT

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

private slots:
  void onControlsClick();
  void onPlayersClick();
  void onArenaClick();
  void onStartClick();
  void onAboutClick();
};

std::vector<SpritePlayer> CreatePlayers(const ArenaSettings& a);
std::vector<SpriteBall> CreateBalls(const ArenaSettings& a) noexcept;
std::vector<SpriteNonMoving> CreateObstacles(const ArenaSettings& a);

} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENMENUDIALOG_H
