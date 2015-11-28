//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

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
#include "boenkencontrols.h"

#include <cassert>
#include <iostream>

std::ostream& ribi::bnkn::operator<<(std::ostream& os, const Controls& c) noexcept
{
  assert(c.m_keys_accel.size() == c.m_keys_turn.size());
  assert(c.m_keys_accel.size() == c.m_names.size());
  const int sz{static_cast<int>(c.m_names.size())};
  for (int i=0; i!=sz; ++i) {
    os << c.m_names[i] << ", " << c.m_keys_accel[i] << ", " << c.m_keys_turn[i] << '\n';
  }
  return os;
}

