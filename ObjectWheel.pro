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

INCLUDEPATH += $$PWD/libcouchbase/src/src-orj/include
DEPENDPATH += $$PWD/libcouchbase/src/src-orj/include
#----------------------------<< LINUX >>-------------------------------
unix:LIBS += -L$$PWD/libcouchbase/linux/lib/ -lcouchbase
#----------------------------------------------------------------------

#---------------------------<< MAC_OSX >>------------------------------
macx:LIBS += -L$$PWD/libcouchbase/mac/lib/ -lcouchbase
#----------------------------------------------------------------------

#---------------------------<< WINDOWS >>------------------------------
#Windows için couchbase kütüphanesi (hem statik hem dinamik'e bu yeter)
win32:LIBS += -L$$PWD/libcouchbase/windows/lib/ -lcouchbase
#Windows için winsock2 kütüphanesi
win32:LIBS += -lws2_32
#Hem statik hem dinamik derleme yapılacaksa ilgili kütüphanenin
#dosyası mesela libcouchbase.a şeklinde olur. Ancak bu karışıklık
#oluşturmaktadır bu nedenle ilgili kütüphanenin statik versiyonunun
#ismi libcouchbase.a şeklinde bırakılırken. Dinamik versiyonu
#libcouchbase.dll.a şeklinde olmalıdır. Böylece linkera tek bir
# -lcouchbase komutu statik derlemede otomatikman birinci dosyayı
#dinamik derlemede ise otomatikman ikinci dosyayı seçtirecektir.
#Bunun yanısıra unutulmamalıdır ki dinamik derlemeden sonra
#yazılımın çalışabilmesi için ilgili dll dosyalarınında build
#klasörüne atılmış olması gerekmektedir. Yoksa başarıyla derlense
#bile program çalışma esnasında cras'a gidecektir.
#----------------------------------------------------------------------

RESOURCES += \
    resource.qrc
