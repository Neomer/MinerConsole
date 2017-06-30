TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
OTHER_FILES += SomeFunc.c

OPENCL_PATH = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v8.0"
# OPENCL
INCLUDEPATH += $$OPENCL_PATH/include
LIBS += -L$$OPENCL_PATH/lib/x64/ -lOpenCL

DISTFILES +=
