#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T14:07:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AImbot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logreader.cpp \
    entitymanager.cpp \
    entity.cpp

HEADERS  += mainwindow.h \
    logreader.h \
    entitymanager.h \
    entity.h

FORMS    += mainwindow.ui

DISTFILES += \
    cards.json
