#-------------------------------------------------
#
# Project created by QtCreator 2017-03-26T15:48:01
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pdq
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        pdqmainwindow.cpp \
    pdfview.cpp \
    searchdialog.cpp \
    searchstate.cpp \
    bookmarks.cpp \
    utils.cpp \
    addbookmark.cpp \
    navdialog.cpp \
    textextract.cpp \
    note.cpp \
    addnote.cpp \
    config.cpp

HEADERS  += pdqmainwindow.h \
    pdfview.h \
    searchdialog.h \
    searchstate.h \
    bookmarks.h \
    utils.h \
    addbookmark.h \
    navdialog.h \
    textextract.h \
    note.h \
    addnote.h \
    config.h

FORMS    += pdqmainwindow.ui \
    searchdialog.ui \
    bookmarks.ui \
    addbookmark.ui \
    navdialog.ui \
    textextract.ui \
    addnote.ui

#INCLUDEPATH += /usr/include/poppler/qt5/
#DEPENDPATH += /usr/lib/x86_64-linux-gnu/

unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}
