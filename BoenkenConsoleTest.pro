include(../RibiLibraries/ConsoleApplicationNoWeffcpp.pri)
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)


include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)

include(BoenkenConsole.pri)
include(BoenkenConsoleTest.pri)

SOURCES += main_test.cpp

# Qt resourse files generate an unused variable warning
QMAKE_CXXFLAGS += -Wno-unused-variable

# Boost.Test
LIBS += -lboost_unit_test_framework