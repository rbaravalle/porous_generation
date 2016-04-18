#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T17:49:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = porous_qt
TEMPLATE = app

CONFIG += c++11



SOURCES += main.cpp\
        mainwindow.cpp \
    Image.cpp \
    Particle.cpp \
    Pixel.cpp \
    Porous.cpp \
    Runge_Kutta.cpp \
    Volumetric_texture.cpp \
    test.cpp

HEADERS  += mainwindow.h \
    Image.h \
    Pixel.hpp \
    Porous.hpp \
    Runge_Kutta.hpp \
    Volumetric_texture.hpp \
    Particle.hpp

FORMS    += mainwindow.ui
