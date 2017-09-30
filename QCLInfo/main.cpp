#include <QCoreApplication>
#include <QDebug>
#include <QLibraryInfo>
#include "qclinfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QLoggingCategory::setFilterRules("*.info=false");
    QLoggingCategory::setFilterRules("clInfo.Methods.Flow.info=false");
    QLoggingCategory::setFilterRules("clInfo.To.Console.info=false");

    qDebug() << "QOpenCL info" ;

    QCLInfo* clInfo = new QCLInfo;
    qDebug() << "OpenCL platforms:" << clInfo->getPlatformNames();
    qDebug() << "OpenCL devices:" << clInfo->getDeviceNames();
    delete clInfo;

    return a.exec();
}
