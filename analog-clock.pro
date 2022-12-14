# -----------------------------------------------------
# Deepak Krishnaa Govindarajan
# Marcus Naess
# Soobin Rho
# November 6, 2022
# COSC 226: C++ Programming
#
# Hw6: Code walkthrough
#
# This file is in charge of storing the project configs
# for Qt Creator. When we open Qt Creator,
# this file is what we open first.
# -----------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += analog-clock.cpp

HEADERS += analog-clock.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
