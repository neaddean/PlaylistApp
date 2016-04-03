TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra

SOURCES += main.cpp \
    songinfo.cpp

HEADERS += \
    songinfo.h

