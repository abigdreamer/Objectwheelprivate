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

RC_ICONS = icon.ico
SOURCES += main.cpp\
        mainwindow.cpp \
    zdragdrop.cpp \
    loginwindow.cpp \
    zwebwidget.cpp \
    zwebbrowser.cpp \
    zvisualregulator.cpp \
    zcouchbasemanager.cpp

HEADERS  += mainwindow.h \
    zdragdrop.h \
    loginwindow.h \
    zwebwidget.h \
    zwebbrowser.h \
    zvisualregulator.h \
    zcouchbasemanager.h

FORMS    += mainwindow.ui \
    loginwindow.ui

RESOURCES += \
    resource.qrc \
    drgdrpres.qrc

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
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
mac{
!ios{
	QT += webkitwidgets
}
}
}

# ADDED FOR JNI
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors
LIBS += -L $(JAVA_HOME)/jre/lib/amd64/server/ \
	-ljvm
INCLUDEPATH += -I $(JAVA_HOME)/include/ \
	-I $(JAVA_HOME)/include/linux/ \

# END
