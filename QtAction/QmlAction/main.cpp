// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/utils/blob/master/LICENSE


//#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../share/share.h"

#include "../share/aobject.h"

int main(int argc, char *argv[])
{
    YA_TIMESTAMP();
    qDebug() << QDateTime::currentMSecsSinceEpoch() << " msec since Epoch is\t"
             << QDateTime::currentDateTime();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QApplication app(argc, argv);
    QGuiApplication app(argc, argv);

    qmlRegisterType<AObject> ("AObject", 1, 0, "AObject");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
