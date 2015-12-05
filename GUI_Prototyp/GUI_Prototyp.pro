#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T14:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_Prototyp
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        hauptfenster.cpp \
    overlay.cpp \
    threadstayhelpontop.cpp

HEADERS  += hauptfenster.h \
    overlay.h \
    threadstayhelpontop.h

FORMS    += hauptfenster.ui \
    overlay.ui

DISTFILES += \
    icons/app-icon.png \
    icons/DataManager.png \
    icons/document-open.png \
    icons/document-save.png \
    icons/edit-delete.png \
    icons/edit-redo.png \
    icons/edit-undo.png \
    icons/StdMultiWidgetEditor.png \
    icons/system-log-out.png \
    icons/context_menu/Remove_48.png \
    icons/context_menu/Save_48.png \
    icons/labsw/dynamic-help.png \
    icons/labsw/background.png

RESOURCES += \
    icons.qrc
