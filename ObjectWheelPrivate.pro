#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T22:37:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjectWheelPrivate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zdragdrop.cpp \
    zdatabasemanager.cpp \
    loginwindow.cpp

HEADERS  += mainwindow.h \
    zdragdrop.h \
    zdatabasemanager.h \
    loginwindow.h

FORMS    += mainwindow.ui \
    loginwindow.ui

RESOURCES += \
    resource.qrc \
    drgdrpres.qrc

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
