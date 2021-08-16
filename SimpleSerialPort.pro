#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T16:45:40
#
#-------------------------------------------------

QT       += core serialport

QT       -= gui

TARGET = SimpleSerialPort
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qcserialportmanager.cpp \
    qckeyboard.cpp

HEADERS += \
    qcserialportmanager.h \
    qckeyboard.h
