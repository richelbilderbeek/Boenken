#include "boenkencontrols.h"

#include <boost/test/unit_test.hpp>

#include "fileio.h"
#include <QFile>

BOOST_AUTO_TEST_CASE(ribi_boenken_controls)
{
  BOOST_CHECK_NO_THROW(ribi::bnkn::Controls());
}

