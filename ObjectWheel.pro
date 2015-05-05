#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T22:37:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjectWheel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zdragdrop.cpp \
    zlayout.cpp \
    zcouchbasemanager.cpp \
    zdesigner.cpp

HEADERS  += mainwindow.h \
    zdragdrop.h \
    zlayout.h \
    zcouchbasemanager.h \
    zdesigner.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
