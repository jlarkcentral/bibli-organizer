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
    livre.cpp \
    biblio.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinystr.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxmlparser.cpp \
    dossier.cpp \
    fichelivre.cpp \
    itemindex.cpp

HEADERS  += mainwindow.h \
    livre.h \
    biblio.h \
    tinyxml/tinyxml.h \
    tinyxml/tinystr.h \
    dossier.h \
    fichelivre.h \
    itemindex.h

FORMS    += mainwindow.ui
