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
    Field.cpp \
    Player.cpp \
    XYCoordinate.cpp \
    DisplayWindow.cpp

HEADERS  += ControlWindow.h \
    Field.h \
    Player.h \
    XYCoordinate.h \
    DisplayWindow.h

FORMS    += ControlWindow.ui \
    DisplayWindow.ui

RESOURCES += \
    images.qrc
