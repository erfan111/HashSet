#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T17:47:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HashSet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hashset.c \
    hashset_itr.c

HEADERS  += mainwindow.h \
    hashset.h \
    hashset_itr.h

FORMS    += mainwindow.ui
