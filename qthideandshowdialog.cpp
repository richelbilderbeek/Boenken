#include "qthideandshowdialog.h"

#include <cassert>

#include <QCloseEvent>
#include <QKeyEvent>

ribi::QtHideAndShowDialog::QtHideAndShowDialog(QWidget* parent) noexcept
  : QDialog(parent)
{
#ifdef Q_OS_WASM
  // The web page is the window: no title bar, top-left of the canvas
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
}

void ribi::QtHideAndShowDialog::closeEvent(QCloseEvent * event)
{
  emit close_me();
  event->accept();
}

void ribi::QtHideAndShowDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
  QDialog::keyPressEvent(event);
}

void ribi::QtHideAndShowDialog::ShowChild(
  QtHideAndShowDialog * const child,
  std::function<void()> on_close
)
{
  assert(child);
  QObject::connect(
    child,
    &QtHideAndShowDialog::close_me,
    this,
    [this, on_close]()
    {
      if (on_close) on_close();
      this->show();
    },
    Qt::SingleShotConnection
  );
  this->hide();
  child->show();
  child->activateWindow();
  child->setFocus();
}

void ribi::QtHideAndShowDialog::showEvent(QShowEvent * event)
{
#ifdef Q_OS_WASM
  move(0, 0);
#endif
  QDialog::showEvent(event);
}
