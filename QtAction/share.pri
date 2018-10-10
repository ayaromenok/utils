# Copyright(C) 2017-2018 Andrey Yaromenok, ayaromenok@gmail.com
# MIT License - https://github.com/ayaromenok/utils/blob/master/LICENSE

HEADERS += \
    $$PWD/share/aobject.h \
    $$PWD/share/share.h
SOURCES += \
    $$PWD/share/aobject.cpp

linux:!android {
    message("* Using settings for Unix/Linux.")
    contains(QMAKE_HOST.arch, x86_64){
        message("        arch: amd64")
    }
    contains(QMAKE_HOST.arch, x86){
        message("        arch: i386")
    }
}
macx{
    message("* Using settings for Mac OS X.")
    contains(QMAKE_HOST.arch, x86_64){
        message("        arch: amd64")
    }
    contains(QMAKE_HOST.arch, x86){
        message("        arch: i386")
    }
 }

win32{
    message("* Using settings for Windows.")
    contains(QMAKE_TARGET.arch, x86_64){
        message("        arch: amd64")
        win32-msvc* {
            MSVC_VER = $$(VisualStudioVersion)
            equals(MSVC_VER, 12.0){
                message("           msvc12 - 2013")
            }
            equals(MSVC_VER, 13.0){
                message("           msvc13 - 2014")
            }
            equals(MSVC_VER, 14.0){
                message("           msvc14 - 2015")
            }
            equals(MSVC_VER, 15.0){
                message("           msvc15 - 2017")
            }
        }
    }
    contains(QMAKE_TARGET.arch, x86){
        message("        arch: i386")
        win32-g++ {
            message("               compiler: mingw-32")
        }
    }

}
