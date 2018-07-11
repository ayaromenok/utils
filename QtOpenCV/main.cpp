#include <QApplication>
#include <QDebug>
//#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "++++++++++++++++++++++++++++++++++++++++++";
    qDebug() << "|\tQt OpenCV stub app  \t|";
    qDebug() << "------------------------------------------";
//    MainWidget w;
//    w.show();

    return a.exec();
}
