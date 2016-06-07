#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T14:07:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = notepad++
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logreader.cpp \
    entitymanager.cpp \
    entity.cpp \
    entitywidget.cpp

HEADERS  += mainwindow.h \
    logreader.h \
    entitymanager.h \
    entity.h \
    entitywidget.h

FORMS    += mainwindow.ui \
    entitywidget.ui

DISTFILES += \
    cards.json
