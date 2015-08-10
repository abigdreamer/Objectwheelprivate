#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T22:37:22
#
#-------------------------------------------------

QT       += core gui uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qtHaveModule(webengine) {
		QT += webengine quickwidgets
		DEFINES += QT_WEBVIEW_WEBENGINE_BACKEND
}else{
QT += quickwidgets
}

TARGET = ObjectWheelPrivate
TEMPLATE = app

RC_ICONS = app.ico
SOURCES += main.cpp\
        mainwindow.cpp \
    zdragdrop.cpp \
    zdatabasemanager.cpp \
    loginwindow.cpp \
    zwebwidget.cpp \
    zwebbrowser.cpp

HEADERS  += mainwindow.h \
    zdragdrop.h \
    zdatabasemanager.h \
    loginwindow.h \
    zwebwidget.h \
    zwebbrowser.h

FORMS    += mainwindow.ui \
    loginwindow.ui

RESOURCES += \
    resource.qrc \
    drgdrpres.qrc

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

!contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
	QT += webkitwidgets
}
