#-------------------------------------------------
#
# Project created by QtCreator 2010-12-15T20:30:16
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Haushaltsbuch
TEMPLATE = app

SOURCES += main.cpp\
           housekeepingbookwindow.cpp \
           addumsatzdialog.cpp \
           pieview.cpp \
           viewproxymodel.cpp \
           treeproxymodel.cpp \
           mysqlrelationaltablemodel.cpp

HEADERS  += housekeepingbookwindow.h \
            datenbank.h \
            addumsatzdialog.h \
            pieview.h \
            viewproxymodel.h \
            treeproxymodel.h \
            mysqlrelationaltablemodel.h

FORMS    +=

OTHER_FILES += \
    README.txt \
    ToDo.txt
