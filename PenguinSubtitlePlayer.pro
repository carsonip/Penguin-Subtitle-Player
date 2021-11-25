#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T11:51:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PenguinSubtitlePlayer
TEMPLATE = app

SOURCES += \
    src/uchardet/src/LangModels/LangArabicModel.cpp \
    src/uchardet/src/LangModels/LangBulgarianModel.cpp \
    src/uchardet/src/LangModels/LangCroatianModel.cpp \
    src/uchardet/src/LangModels/LangCzechModel.cpp \
    src/uchardet/src/LangModels/LangDanishModel.cpp \
    src/uchardet/src/LangModels/LangEsperantoModel.cpp \
    src/uchardet/src/LangModels/LangEstonianModel.cpp \
    src/uchardet/src/LangModels/LangFinnishModel.cpp \
    src/uchardet/src/LangModels/LangFrenchModel.cpp \
    src/uchardet/src/LangModels/LangGermanModel.cpp \
    src/uchardet/src/LangModels/LangGreekModel.cpp \
    src/uchardet/src/LangModels/LangHebrewModel.cpp \
    src/uchardet/src/LangModels/LangHungarianModel.cpp \
    src/uchardet/src/LangModels/LangIrishModel.cpp \
    src/uchardet/src/LangModels/LangItalianModel.cpp \
    src/uchardet/src/LangModels/LangLatvianModel.cpp \
    src/uchardet/src/LangModels/LangLithuanianModel.cpp \
    src/uchardet/src/LangModels/LangMalteseModel.cpp \
    src/uchardet/src/LangModels/LangPolishModel.cpp \
    src/uchardet/src/LangModels/LangPortugueseModel.cpp \
    src/uchardet/src/LangModels/LangRomanianModel.cpp \
    src/uchardet/src/LangModels/LangRussianModel.cpp \
    src/uchardet/src/LangModels/LangSlovakModel.cpp \
    src/uchardet/src/LangModels/LangSloveneModel.cpp \
    src/uchardet/src/LangModels/LangSpanishModel.cpp \
    src/uchardet/src/LangModels/LangSwedishModel.cpp \
    src/uchardet/src/LangModels/LangThaiModel.cpp \
    src/uchardet/src/LangModels/LangTurkishModel.cpp \
    src/uchardet/src/LangModels/LangVietnameseModel.cpp \
    src/uchardet/src/CharDistribution.cpp \
    src/uchardet/src/JpCntx.cpp \
    src/uchardet/src/nsBig5Prober.cpp \
    src/uchardet/src/nsCharSetProber.cpp \
    src/uchardet/src/nsEscCharsetProber.cpp \
    src/uchardet/src/nsEscSM.cpp \
    src/uchardet/src/nsEUCJPProber.cpp \
    src/uchardet/src/nsEUCKRProber.cpp \
    src/uchardet/src/nsEUCTWProber.cpp \
    src/uchardet/src/nsGB2312Prober.cpp \
    src/uchardet/src/nsHebrewProber.cpp \
    src/uchardet/src/nsLatin1Prober.cpp \
    src/uchardet/src/nsMBCSGroupProber.cpp \
    src/uchardet/src/nsMBCSSM.cpp \
    src/uchardet/src/nsSBCharSetProber.cpp \
    src/uchardet/src/nsSBCSGroupProber.cpp \
    src/uchardet/src/nsSJISProber.cpp \
    src/uchardet/src/nsUniversalDetector.cpp \
    src/uchardet/src/nsUTF8Prober.cpp \
    src/uchardet/src/uchardet.cpp

HEADERS += \
    src/uchardet/src/CharDistribution.h \
    src/uchardet/src/JpCntx.h \
    src/uchardet/src/nsBig5Prober.h \
    src/uchardet/src/nsCharSetProber.h \
    src/uchardet/src/nsCodingStateMachine.h \
    src/uchardet/src/nscore.h \
    src/uchardet/src/nsEscCharsetProber.h \
    src/uchardet/src/nsEUCJPProber.h \
    src/uchardet/src/nsEUCKRProber.h \
    src/uchardet/src/nsEUCTWProber.h \
    src/uchardet/src/nsGB2312Prober.h \
    src/uchardet/src/nsHebrewProber.h \
    src/uchardet/src/nsLatin1Prober.h \
    src/uchardet/src/nsMBCSGroupProber.h \
    src/uchardet/src/nsPkgInt.h \
    src/uchardet/src/nsSBCharSetProber.h \
    src/uchardet/src/nsSBCSGroupProber.h \
    src/uchardet/src/nsSJISProber.h \
    src/uchardet/src/nsUniversalDetector.h \
    src/uchardet/src/nsUTF8Prober.h \
    src/uchardet/src/prmem.h \
    src/uchardet/src/uchardet.h \
    src/uchardet/src/Big5Freq.tab \
    src/uchardet/src/EUCKRFreq.tab \
    src/uchardet/src/EUCTWFreq.tab \
    src/uchardet/src/GB2312Freq.tab \
    src/uchardet/src/JISFreq.tab

SOURCES += \
    src/configdialog.cpp \
    src/main.cpp \
    src/clickablelabel.cpp \
    src/mainwindow.cpp \
    src/pages.cpp \
    src/prefpage.cpp \
    src/chardet.cpp \
    src/parsers/srtparser.cpp \
    src/parsers/ssaparser.cpp \
    src/parsers/webvttparser.cpp \
    src/parser.cpp \
    src/engine.cpp \
    src/nccdialog.cpp

HEADERS += \
    src/configdialog.h \
    src/clickablelabel.h \
    src/mainwindow.h \
    src/pages.h \
    src/prefpage.h \
    src/prefconstants.h \
    src/chardet.h \
    src/parsers/srtparser.h \
    src/parsers/ssaparser.h \
    src/parsers/webvttparser.h \
    src/parserinterface.h \
    src/parser.h \
    src/engine.h \
    src/nccdialog.h

FORMS    += \
    resource/ui/mainwindow.ui

CONFIG += c++11

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

VERSION = 1.6.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

test { # the following files will be included for Unit test build
    message(Test build)

    QT += testlib #needed for QtTest
    SOURCES -= src/main.cpp

    HEADERS += \
    src/test/parsers/testssaparser.h \
    src/test/tests.h \
    src/test/parsers/testsrtparser.h \
    src/test/parsers/testwebvttparser.h \
    src/test/testengine.h \
    src/test/parsers/parsertests.h

    SOURCES += \
    src/test/parsers/testssaparser.cpp \
    src/test/main.cpp \
    src/test/tests.cpp \
    src/test/parsers/testsrtparser.cpp \
    src/test/parsers/testwebvttparser.cpp \
    src/test/testengine.cpp \
    src/test/parsers/parsertests.cpp
} else {
    message(Normal build) #we will just show this message for Debug/Release build
}

win32 {
    RC_ICONS=resource\icon.ico
}

macx {
    ICON=resource/icon.icns
}

unix:!macx {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    isEmpty(BINDIR) {
        BINDIR = $$PREFIX/bin
    }
    isEmpty(DATADIR) {
        DATADIR = $$PREFIX/share
    }

    target.path = $$BINDIR

    icon.files = resource/icons/hicolor/*
    icon.path = $$DATADIR/icons/hicolor

    desktop.files = resource/PenguinSubtitlePlayer.desktop
    desktop.path = $$DATADIR/applications/

    appdata.files = resource/PenguinSubtitlePlayer.appdata.xml
    appdata.path = $$DATADIR/metainfo/

    INSTALLS += target icon desktop appdata
}
