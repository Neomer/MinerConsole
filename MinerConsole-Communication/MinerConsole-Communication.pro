#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T15:32:51
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = mccomm
TEMPLATE = lib

DEFINES += MINERCONSOLECOMMUNICATION_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        MinerConsoleCommunication.cpp \
    MCCommPackage.cpp \
    TVersion.cpp \
    IController.cpp

HEADERS += \
        MinerConsoleCommunication.h \
        minerconsole-communication_global.h \ 
    MCCommPackage.h \
    TVersion.h \
    Err.h \
    IController.h \
    IControllerPoint.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += "C:\\Users\\user\\Downloads\\boost_1_64_0"

OBJECTS_DIR = ../tmp/$$TARGET
UI_DIR = ../tmp/$$TARGET
MOC_DIR = ../tmp/$$TARGET

