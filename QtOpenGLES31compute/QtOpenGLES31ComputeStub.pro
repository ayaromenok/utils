QT       += core gui widgets

TARGET = QtOpenGLES31ComputeStub
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
    res/main.fsh \
    res/main.gsh
