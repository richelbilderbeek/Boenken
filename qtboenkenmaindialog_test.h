#ifndef QTBOENKENMAINDIALOGTEST_H
#define QTBOENKENMAINDIALOGTEST_H

#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QtTest/QtTest>
#pragma GCC diagnostic pop

namespace ribi {
namespace bnkn {

class qtboenkenmaindialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void all_tests();
};


} //~namespace bnkn
} //~namespace ribi

#endif // QTBOENKENMAINDIALOGTEST_H
