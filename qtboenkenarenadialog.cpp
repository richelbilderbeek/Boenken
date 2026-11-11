

#include "qtboenkenarenadialog.h"

#include <cassert>
#include <stdexcept>

#include <QScreen>

#include "ui_qtboenkenarenadialog.h"


ribi::bnkn::QtArenaDialog::QtArenaDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtBoenkenArenaDialog)
{
  ui->setupUi(this);
  QObject::connect(ui->button_done,SIGNAL(clicked(bool)),this,SLOT(close()));
}

ribi::bnkn::QtArenaDialog::~QtArenaDialog() noexcept
{
  delete ui;
}

///The purpose of QtBoenkenArenaDialog is to create
///an ArenaSettings
ribi::bnkn::ArenaSettings ribi::bnkn::QtArenaDialog::GetSettings() const noexcept
{
  ArenaSettings s;
  s.formation = this->GetFormation();
  s.friction = this->GetFriction();
  s.n_balls = this->GetNballs();
  s.n_obstacles = this->GetNobstacles();
  s.screen_size = this->GetScreenSize();
  return s;
}

std::pair<int,int> ribi::bnkn::QtArenaDialog::GetScreenSize() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_screen_size;
  assert(b->count()==2);
  if (b->currentIndex() == 0)
  {
    assert(b->currentText() == "Full screen");
    const QRect screen{this->screen()->availableGeometry()};
#ifdef Q_OS_WASM
    // The screen is the canvas on the web page
    return std::make_pair(screen.width(), screen.height());
#else
    // -8, because of the application frame
    // -50, because of the app's title bar
    return std::make_pair(screen.width() - 8, screen.height() - 50);
#endif
  }
  assert(b->currentIndex() == 1);
  assert(b->currentText() == "640x400");
  return std::make_pair(640,400);
}

int ribi::bnkn::QtArenaDialog::GetNballs() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_nballs;
  assert(b->count() == 2);
  if (b->currentIndex() == 0)
  {
    assert(b->currentText() == "One");
    return 1;
  }
  assert(b->currentIndex() == 1);
  assert(b->currentText() == "Two");
  return 2;
}

int ribi::bnkn::QtArenaDialog::GetNobstacles() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_obstacles;
  assert(b->count()==2);
  if (b->currentIndex() == 0)
  {
    assert(b->currentText() == "None");
    return 0;
  }
  assert(b->currentIndex() == 1);
  assert(b->currentText() == "Two");
  return 2;
}

ribi::bnkn::Formation ribi::bnkn::QtArenaDialog::GetFormation() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_formation;
  assert(b->count()==3);
  if (b->currentIndex() == 0)
  {
    assert(b->currentText() == "Line");
    return Formation::straight_line;
  }
  else if (b->currentIndex() == 1)
  {
    assert(b->currentText() == "Circle, inward");
    return Formation::circle_inward;
  }
  assert(b->currentIndex() == 2);
  assert(b->currentText() == "Circle, outward");
  return Formation::circle_outward;
}

double ribi::bnkn::QtArenaDialog::GetFriction() const noexcept
{
  const QComboBox * const b = ui->box_friction;
  assert(b->count()==3);
  if (b->currentIndex() == 0)
  {
      assert(b->currentText() == "None");
      return 1.0;
  }
  else if (b->currentIndex() == 1)
  {
    assert(b->currentText() == "Low");
    return 0.999;
  }
  assert(b->currentIndex() == 2);
  assert(b->currentText() == "Medium");
  return 0.99;
}

