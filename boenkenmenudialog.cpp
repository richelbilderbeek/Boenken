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
#include "boenkenmenudialog.h"

#include <cassert>
#include <iostream>

#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "testtimer.h"
#include "trace.h"

ribi::bnkn::MenuDialog::MenuDialog()
{
}

int ribi::bnkn::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  std::cout
    << this->GetAbout().GetFileTitle() << " cannot be run in console mode\n"
    << std::endl;
  return 0;
}

ribi::About ribi::bnkn::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Boenken",
    "a multiplayer soccer/billiards game",
    "January 9th 2016",
    "2007-2016",
    "http://www.richelbilderbeek.nl/GameBoenken.htm",
    GetVersion(),
    GetVersionHistory()
  );

  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  return a;
}

ribi::Help ribi::bnkn::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::bnkn::MenuDialog::GetVersion() const noexcept
{
  return "5.2";
}

std::vector<std::string> ribi::bnkn::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2000-xx-xx: version 0.0: wrote QBASIC version of Boenken",
    "2007-10-18: version 1.0: port from QBASIC to C++ Builder",
    "2007-12-30: version 2.0: added old-school-graphics mode, "
      "two-button control and option to set the friction of the players",
    "2010-08-14: version 3.0: initial port to cross-platform, "
      "using Qt Creator. Added doxygen support",
    "2010-08-15: version 3.1: created basic menu functionality, "
      "improved doxygen documentation, "
      "improved code (seperated GUI from game rules, "
      "all sprites can be deleted by boost::checked_delete only)",
    "2012-03-07: version 4.0: conformized naming and architecture "
      "for ProjectRichelBilderbeek"
    "2012-11-17: version 4.1: added a fancy color gradient to the main menu",
    "2015-01-02: version 4.2: fixed bug in collision between player and object",
    "2015-11-15: version 5.0: moved to own GitHub",
    "2015-11-28: version 5.1: made many types regular",
    "2016-01-09: version 5.2: crosscompiles again",
  };
}
