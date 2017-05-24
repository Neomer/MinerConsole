QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinerConsole.Admin
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/MainForm.cpp

FORMS += \
    src/MainForm.ui

HEADERS += \
    src/MainForm.h

OBJECTS_DIR = ../tmp/$$TARGET
UI_DIR = ../tmp/$$TARGET
MOC_DIR = ../tmp/$$TARGET
