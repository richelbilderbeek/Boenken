#ifndef BOENKENSPRITENONMOVINGTEST_H
#define BOENKENSPRITENONMOVINGTEST_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QtTest/QtTest>
#pragma GCC diagnostic pop

namespace ribi {
namespace bnkn {

class qtboenkenspritenonmoving_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void all_tests();
};


} //~namespace bnkn
} //~namespace ribi

#endif // BOENKENSPRITENONMOVINGTEST_H
