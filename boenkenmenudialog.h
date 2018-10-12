#ifndef BOENKENMENUDIALOG_H
#define BOENKENMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

namespace bnkn {

struct MenuDialog final : public ::ribi::MenuDialog
{
  MenuDialog();
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace bnkn

} //~namespace ribi

#endif // BOENKENMENUDIALOG_H
