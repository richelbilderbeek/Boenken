include(../RibiLibraries/DesktopApplicationNoWeffcpp.pri)

include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralDesktop.pri)

include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)

include(BoenkenDesktop.pri)
include(BoenkenDesktopTest.pri)

SOURCES += qtmain_test.cpp

# Qt resourse files generate an unused variable warning
QMAKE_CXXFLAGS += -Wno-unused-variable

# QtTest generates this
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs

# QTest
QT += testlib
