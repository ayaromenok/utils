TARGET      = QtOpenCV
TEMPLATE    = app
QT  += core gui widgets
QT  += multimedia multimediawidgets
CONFIG += c++11

#change path to OpenCV SDK here. this one used *.so, but can be changed to *.a
CV3ANDROID = /home/az/sdk/android/opencv/3/sdk/native
include(opencv.pri)  #OpenCV stuff here
include(android.pri) #Android standard stuff here
SOURCES += \
        main.cpp \
    cvwidget.cpp

RESOURCES += \
    res.qrc

HEADERS += \
    cvwidget.h
