QT += core network
QT -= gui

CONFIG += c++11


TARGET = MinerConsole-Miner
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/interfaces/IMiner.cpp \
    src/interfaces/IJob.cpp \
    src/interfaces/IJobDispatcher.cpp \
    src/logs/Logger.cpp \
    src/StratumParser.cpp \
    src/algo/Blake2b.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    src/interfaces/IMiner.h \
    src/interfaces/IJob.h \
    src/interfaces/IJobDispatcher.h \
    src/logs/Logger.h \
    src/StratumParser.h \
    src/interfaces/ISingleton.h \
    src/algo/Blake2b.h

INCLUDEPATH += $$PWD

QMAKE_CXXFLAGS += -DNDEBUG -g2 -O3
INCLUDEPATH += C:/cryptopp565
LIBS += -LC:/cryptopp565/release -lcryptopp


OBJECTS_DIR = ../tmp/$$TARGET
UI_DIR = ../tmp/$$TARGET
MOC_DIR = ../tmp/$$TARGET

