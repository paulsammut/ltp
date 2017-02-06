#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T20:47:34
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LTP_Manager
TEMPLATE = app


SOURCES += main.cpp\
        ltp_manager.cpp \
    packet.cpp \
    handlepacket.cpp

HEADERS  += ltp_manager.h \
    packet.h \
    handlepacket.h

FORMS    += ltp_manager.ui
