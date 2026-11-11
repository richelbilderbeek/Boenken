#ifndef QTHIDEANDSHOWDIALOG_H
#define QTHIDEANDSHOWDIALOG_H

#include <functional>

#include <QDialog>

namespace ribi {

///A dialog that hides itself while it shows a child dialog,
///and shows itself again when the child is closed.
///
///This never starts a nested event loop (no QDialog::exec),
///as nested event loops do not work in the WebAssembly version.
class QtHideAndShowDialog : public QDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtHideAndShowDialog(QWidget* parent = nullptr) noexcept;
  virtual ~QtHideAndShowDialog() = default;

  ///Hide this dialog and show the child.
  ///When the child is closed, 'on_close' is called
  ///and this dialog is shown again
  void ShowChild(
    QtHideAndShowDialog * const child,
    std::function<void()> on_close = {}
  );

signals:
  ///Emitted when this dialog is closed
  void close_me();

protected:
  void closeEvent(QCloseEvent * event) override;

  ///Close on escape key
  void keyPressEvent(QKeyEvent* event) override;

  void showEvent(QShowEvent * event) override;
};

} //~namespace ribi

#endif // QTHIDEANDSHOWDIALOG_H
