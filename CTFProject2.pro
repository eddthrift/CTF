#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T15:34:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTFProject2
TEMPLATE = app


SOURCES += main.cpp\
        ControlWindow.cpp \
    Player.cpp \
    XYCoordinate.cpp \
    DisplayWindow.cpp \
    Game.cpp \
    Field.cpp

HEADERS  += ControlWindow.h \
    Player.h \
    XYCoordinate.h \
    DisplayWindow.h \
    Game.h \
    Field.h

FORMS    += ControlWindow.ui \
    DisplayWindow.ui

RESOURCES += \
    images.qrc
