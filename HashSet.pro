QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HashSet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hashset.c

HEADERS  += mainwindow.h \
    hashset.h

FORMS    += mainwindow.ui
