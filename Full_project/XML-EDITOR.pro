#-------------------------------------------------
#
# Project created by QtCreator 2021-12-14T15:33:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XML-EDITOR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xml-consistency.cpp \
    minifying.cpp \
    compression.cpp \
    xml2json.cpp \
    xml_formatter.cpp

HEADERS  += mainwindow.h \
    xml-consistency.h \
    minifying.h \
    compression.h \
    hash_map.h \
    hash_node.h \
    xml2json.h \
    xml_formatter.h

FORMS    += mainwindow.ui
