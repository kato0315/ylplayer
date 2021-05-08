#-------------------------------------------------
#
# Project created by QtCreator 2021-04-15T11:29:12
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ylplayer
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    filewidget.cpp \
    playwidget.cpp \
    server.cpp \
    toolbutton.cpp

HEADERS  += dialog.h \
    filewidget.h \
    playwidget.h \
    server.h \
    toolbutton.h

FORMS    += dialog.ui \
    filewidget.ui \
    playwidget.ui

RESOURCES += \
    resource/resource.qrc
