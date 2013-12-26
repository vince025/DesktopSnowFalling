#-------------------------------------------------
#
# Project created by QtCreator 2013-12-24T23:16:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesktopSnow
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    snowwidget.cpp \
    swing.cpp

HEADERS  += widget.h \
    snowwidget.h \
    swing.h

FORMS    += widget.ui \
    snowwidget.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ico.rc
RC_FILE += \
	ico.rc
