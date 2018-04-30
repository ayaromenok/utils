#include "mainwindow.h"
#include <QGuiApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);

    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 4.3 core context");
        fmt.setVersion(4, 2);
        fmt.setProfile(QSurfaceFormat::CoreProfile); //renderdoc required core
    } else {
        qDebug("Requesting 3.1 context");
        fmt.setVersion(3, 1);
    }

    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w;
    w.show();

    return a.exec();
}
