#-------------------------------------------------
#
# Project created by QtCreator 2010-12-15T20:30:16
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Haushaltsbuch
TEMPLATE = app

INCLUDEPATH = ./include

SOURCES += source/main.cpp\
           source/housekeepingbookwindow.cpp \
           source/addumsatzdialog.cpp \
           source/pieview.cpp \
           source/viewproxymodel.cpp \
           source/treeproxymodel.cpp

HEADERS  += include/housekeepingbookwindow.h \
            include/datenbank.h \
            include/addumsatzdialog.h \
            include/pieview.h \
            include/viewproxymodel.h \
            include/treeproxymodel.h

FORMS    +=
