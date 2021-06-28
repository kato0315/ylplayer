#-------------------------------------------------
#
# Project created by QtCreator 2021-04-15T11:29:12
#
#-------------------------------------------------

QT       += core gui network multimedia
QT       += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ylplayer
TEMPLATE = app


INCLUDEPATH += "..\\ylplayer\\dependency\\ffmpeg-4.4-full_build-shared\\include"
LIBS += -L..\\ylplayer\\dependency\\ffmpeg-4.4-full_build-shared\\lib -lavcodec -lavformat -lavutil -lavfilter -lswscale -lswresample
LIBS += -lshlwapi

SOURCES += main.cpp\
        dialog.cpp \
    filewidget.cpp \
    playwidget.cpp \
    server.cpp \
    systemvolume.cpp \
    toolbutton.cpp

HEADERS  += dialog.h \
    filewidget.h \
    playwidget.h \
    server.h \
    systemvolume.h \
    toolbutton.h

FORMS    += dialog.ui \
    filewidget.ui

RESOURCES += \
    resource/resource.qrc
