#include <QApplication>
#include <QDebug>
#include "cvwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "++++++++++++++++++++++++++++++++++++++++++";
    qDebug() << "|\tQt OpenCV stub app  \t|";
    qDebug() << "------------------------------------------";
    CvWidget w;
    w.show();

    return a.exec();
}
