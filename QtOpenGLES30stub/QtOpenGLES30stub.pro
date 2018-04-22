QT       += core gui widgets

TARGET = QtOpenGLES30Stub
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

RESOURCES += \
    res.qrc

DISTFILES += \
    res/main.vsh \
    res/main.fsh
