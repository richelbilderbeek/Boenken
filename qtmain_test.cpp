#include <iostream>

#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QtTest/QtTest>
#pragma GCC diagnostic pop

#include "qtboenkenmaindialog_test.h"
#include "qtboenkenspritenonmoving_test.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;

  //These are all tests in alphabetical order
  { ribi::bnkn::qtboenkenmaindialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::bnkn::qtboenkenspritenonmoving_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
