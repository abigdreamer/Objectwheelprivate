#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T00:26:12
#
#-------------------------------------------------

QT       -= gui

TARGET = zcouchbasemanager
TEMPLATE = lib

DEFINES += ZCOUCHBASEMANAGER_LIBRARY

SOURCES += zcouchbasemanager.cpp

HEADERS += zcouchbasemanager.h\
        zcouchbasemanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# ADDED FOR JNI
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors
LIBS += -L $(JAVA_HOME)/jre/lib/amd64/server/ \
	-ljvm
INCLUDEPATH += -I $(JAVA_HOME)/include/ \
	-I $(JAVA_HOME)/include/linux/ \
# END
