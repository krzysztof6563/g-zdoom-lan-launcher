#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T18:05:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = launcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    res.qrc

TRANSLATIONS+=  translations/launcher_pl_PL.ts

TRANSLATIONS+=  translations/launcher_en_EN.ts