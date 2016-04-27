#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T14:22:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Playlist_GUI
TEMPLATE = app

win32:RC_ICONS += logo.ico
ICON = logo.icns

QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra
CONFIG += c++14
CONFIG -= app_bundle

SOURCES += main.cpp\
        mainwindow.cpp \
    songinfo.cpp

HEADERS  += mainwindow.h \
    songinfo.h

FORMS    += mainwindow.ui
