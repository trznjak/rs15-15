#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T18:26:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TjuringSimulator
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    graphgraphicsscene.cpp \
    instructionlab.cpp \
    node.cpp \
    transition.cpp

HEADERS  += mainwindow.h \
    enumeration.h \
    graph.h \
    graphgraphicsscene.h \
    instructionlab.h \
    node.h \
    transition.h

FORMS    += mainwindow.ui \
    graph.ui
