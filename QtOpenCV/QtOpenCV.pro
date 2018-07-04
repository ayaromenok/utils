TEMPLATE = app
CONFIG += console c++11
CONFIG = -app_bundle

SOURCES += \
        main.cpp

linux:!android {
    message("* Using settings for Unix/Linux.")
    LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio
} android {
    message("* Using settings for Android.")
    INCLUDEPATH += "$$PWD/sdk/android/opencv/3/sdk/native/jni/include"
    LIBS += -L "$$PWD/sdk/android/opencv/3/sdk/native/staticlibs/armeabi-v7a"
    LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio
} mac {
    macx {
        message ("* Using settings for OSX")
        LIBS += -framework OpenCV
    }
    ios {
        message ("* Using settings for iOS")
        message ("iOS OpenCL framework doesn't exist even throught PrivateFramework un iPhoneOS SDK 11")
    }
} win32 {
    message ("* Using settings for Windows")
    INCLUDEPATH += "$$PWD/CL/include"
# mingw builds only - it's get everything from *.dll. MS/Intel compilers required corresponding OpenCL.lib file
    LIBS +=C:/Windows/System32/OpenCV.dll
}
