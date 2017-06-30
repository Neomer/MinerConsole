# Directory settings
OPENCL_PATH = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v8.0"
AMD_VERSION = 2.9-1
AMD_SDK_PATH = "C:/Users/user/AMD APP SDK/$$AMD_VERSION"
# /Directory settings



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

# CRYPTOPP Library
#QMAKE_CXXFLAGS += -DNDEBUG -g2 -O3
INCLUDEPATH += C:/cryptopp565
#LIBS += -LC:/cryptopp565/release -lcryptopp
LIBS += -lC:/cryptopp565/x64/DLL_Output/Release/cryptopp

#CUDA SDK
#CUDA_OBJECTS_DIR = release/cuda

#CUDA_SDK = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v8.0"   # Path to cuda SDK install
#SYSTEM_NAME = Win32         # Depending on your system either 'Win32', 'x64', or 'Win64'
#SYSTEM_TYPE = 32            # '32' or '64', depending on your system
#CUDA_ARCH = sm_11           # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
#NVCC_OPTIONS = --use_fast_math

#QMAKE_LIBDIR += $$CUDA_SDK/lib/$$SYSTEM_NAME
#LIBS += -L$$CUDA_SDK/lib/$$SYSTEM_NAME
#INCLUDEPATH += $$CUDA_SDK/include
#LIBS += -lOpenCL
# The following library conflicts with something in Cuda
#MSVCRT_LINK_FLAG_DEBUG = "/MDd"
#MSVCRT_LINK_FLAG_RELEASE = "/MD"

# OPENCL
INCLUDEPATH += $$OPENCL_PATH/include
LIBS += -L$$OPENCL_PATH/lib/x64/ -lOpenCL

# AMD
LIBS += -L$$AMD_SDK_PATH/lib/x86/ -lglew32 -lglut32
INCLUDEPATH += $$AMD_SDK_PATH/include/SDKUtil

OBJECTS_DIR = ../tmp/$$TARGET
UI_DIR = ../tmp/$$TARGET
MOC_DIR = ../tmp/$$TARGET

