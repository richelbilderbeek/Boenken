#ifndef QTBOENKENARENADIALOG_H
#define QTBOENKENARENADIALOG_H



#include "qthideandshowdialog.h"
#include "boenkenarenasettings.h"


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
  Q_OBJECT //!OCLINT

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
