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
    src/srtengine.h

FORMS    += \
    resource/ui/mainwindow.ui

CONFIG += static \
        c++11

RESOURCES += \
    resource/resource.qrc

release:DESTDIR = build/release
release:OBJECTS_DIR = build/release/.obj
release:MOC_DIR = build/release/.moc
release:RCC_DIR = build/release/.rcc
release:UI_DIR = build/release/.ui

debug:DESTDIR = build/debug
debug:OBJECTS_DIR = build/debug/.obj
debug:MOC_DIR = build/debug/.moc
debug:RCC_DIR = build/debug/.rcc
debug:UI_DIR = build/debug/.ui
