#CV3ANDROID should be defined on root *.pro file
linux:!android {
    message("* Using settings for Unix/Linux.")
    contains(QMAKE_HOST.arch, x86_64){
        message("        arch: amd64")
    }
    contains(QMAKE_HOST.arch, x86){
        message("        arch: i386")
    }
    LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_videoio \
            -lopencv_imgproc -lopencv_highgui
}

android {
    INCLUDEPATH += "$${CV3ANDROID}/jni/include"
    message("* Using settings for Android.")
    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        message("        arch: armeabi-v7a")
        LIBS += -L$${CV3ANDROID}/libs/armeabi-v7a
        LIBS += -lopencv_java3

       ANDROID_EXTRA_LIBS = \
           $${CV3ANDROID}/libs/armeabi-v7a/libopencv_java3.so
    }
}
