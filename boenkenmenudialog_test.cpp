#include "boenkenmenudialog.h"

#include <boost/test/unit_test.hpp>

#include "fileio.h"
#include <QFile>

BOOST_AUTO_TEST_CASE(ribi_boenken_menu_dialog)
{
  ribi::bnkn::MenuDialog d;
  BOOST_CHECK(!d.GetVersion().empty());
  BOOST_CHECK(!d.GetVersionHistory().empty());
}

