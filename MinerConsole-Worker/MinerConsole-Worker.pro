QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinerConsole.Worker
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/MainForm.cpp \
    src/StatusBarTimeDisplay.cpp \
    src/StatusBarMinerState.cpp \
    src/Miner.cpp \
    src/AdminPipe.cpp \
    src/AdminListener.cpp

HEADERS += \
    src/MainForm.h \
    src/StatusBarTimeDisplay.h \
    src/StatusBarMinerState.h \
    src/Miner.h \
    src/AdminPipe.h \
    src/AdminListener.h

FORMS += \
    src/MainForm.ui \
    src/StatusBarTimeDisplay.ui \
    src/StatusBarMinerState.ui

OBJECTS_DIR = ../tmp/$$TARGET
UI_DIR = ../tmp/$$TARGET
MOC_DIR = ../tmp/$$TARGET
