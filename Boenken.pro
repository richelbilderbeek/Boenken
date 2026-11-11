lessThan(QT_MAJOR_VERSION, 6): error("Boenken needs Qt 6")

QT       += core gui widgets

TARGET = boenken
TEMPLATE = app
CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

!wasm:!msvc {
  QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
}

SOURCES += \
    boenkencontrols.cpp \
    qtboenkenarenadialog.cpp \
    qtboenkencontrolsdialog.cpp \
    qtboenkengame.cpp \
    qtboenkenmaindialog.cpp \
    qtboenkenmenudialog.cpp \
    qtboenkenplayersdialog.cpp \
    qtboenkenpresskeydialog.cpp \
    qtboenkensprite.cpp \
    qtboenkenspriteball.cpp \
    qtboenkenspritemoving.cpp \
    qtboenkenspritenonmoving.cpp \
    qtboenkenspriteplayer.cpp \
    qthideandshowdialog.cpp \
    qtmain.cpp

HEADERS += \
    boenkenarenasettings.h \
    boenkencontrols.h \
    qtboenkenarenadialog.h \
    qtboenkencontrolsdialog.h \
    qtboenkengame.h \
    qtboenkenmaindialog.h \
    qtboenkenmenudialog.h \
    qtboenkenplayersdialog.h \
    qtboenkenpresskeydialog.h \
    qtboenkensprite.h \
    qtboenkenspriteball.h \
    qtboenkenspritemoving.h \
    qtboenkenspritenonmoving.h \
    qtboenkenspriteplayer.h \
    qthideandshowdialog.h

FORMS += \
    qtboenkenarenadialog.ui \
    qtboenkencontrolsdialog.ui \
    qtboenkenmaindialog.ui \
    qtboenkenmenudialog.ui \
    qtboenkenplayersdialog.ui \
    qtboenkenpresskeydialog.ui

RESOURCES += \
    Boenken.qrc
