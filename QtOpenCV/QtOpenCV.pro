TEMPLATE = app
CONFIG += console c++11

CV3ANDROID = /home/az/sdk/android/opencv/3/sdk/native

SOURCES += \
        main.cpp


linux:!android {
    message("* Using settings for Unix/Linux.")
    LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_videoio \
            -lopencv_imgproc -lopencv_highgui
}

android {
    INCLUDEPATH += "$${CV3ANDROID}/jni/include"

    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        message("Android/armv7")
        LIBS += -L$${CV3ANDROID}/libs/armeabi-v7a
        LIBS += -lopencv_java3

       ANDROID_EXTRA_LIBS = \
           $${CV3ANDROID}/libs/armeabi-v7a/libopencv_java3.so \
           $${CV3ANDROID}/libs/armeabi-v7a/libnative_camera_r4.4.0.so
    }
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
