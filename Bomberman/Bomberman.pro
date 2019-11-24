#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T19:02:05
#
#-------------------------------------------------

QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bomberman
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    bomba.cpp \
    zarek.cpp \
    razbitina.cpp \
    player.cpp

HEADERS  += \
    game.h \
    bomba.h \
    zarek.h \
    razbitina.h \
    prostor.h \
    dodatek.h \
    player.h


FORMS    +=

RESOURCES += \
    res.qrc
