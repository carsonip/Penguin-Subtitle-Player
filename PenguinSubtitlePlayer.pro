#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T11:51:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PenguinSubtitlePlayer
TEMPLATE = app

SOURCES += src/configdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pages.cpp \
    src/prefpage.cpp \
    src/srtengine.cpp

HEADERS  += src/configdialog.h \
    src/mainwindow.h \
    src/pages.h \
    src/prefpage.h \
    src/srtengine.h \
    src/prefconstants.h

FORMS    += \
    resource/ui/mainwindow.ui

CONFIG += static \
        c++11

RESOURCES += \
    resource/resource.qrc
    
CONFIG(debug, debug|release) {
    DESTDIR = build/debug
} else {
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

VERSION = 0.1.0
