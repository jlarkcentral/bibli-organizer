#-------------------------------------------------
#
# Project created by QtCreator 2013-04-14T15:10:42
#
#-------------------------------------------------

QT       += core gui

TARGET = BiblioApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    auteur.cpp \
    groupe.cpp \
    livre.cpp \
    biblio.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinystr.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxmlparser.cpp

HEADERS  += mainwindow.h \
    groupe.h \
    livre.h \
    biblio.h \
    auteur.h \
    tinyxml/tinyxml.h \
    tinyxml/tinystr.h

FORMS    += mainwindow.ui
