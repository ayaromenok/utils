#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

int parseFileList(QVector<QStringList> &fileList){
    for (int i=0; i<fileList.length(); i++){
        qDebug() <<fileList.at(i);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    QDir dir;
    QStringList dirList;
    QString dirArch;
    QVector<QStringList> testFileList;
    QCoreApplication a(argc, argv);
    qDebug() << "Compare results from opencv_perf/test ";
    qDebug() << "run at" << QDir::current();
    if (argc > 1)
    {
         qDebug() << "arch dir:" << argv[1];
         dirArch.append(argv[1]);
    } else {
        qDebug() << "no arch dir selected, use default: Rk3399";
        dirArch.append("Rk3399");
    }

    dir.cd(dirArch);
    dirList = dir.entryList();

    // dirList start with current dir(".") and upper dir(".."), so drop them
    for (int i=2; i< dirList.length(); i++){
        dir.cd(dirList.at(i));
        QStringList list = dir.entryList(QDir::Files);
        //store dir name as first element;
        list.insert(0,dirList.at(i));
        testFileList.append(list);
        dir.cdUp();
    }
    parseFileList(testFileList);
    return 0;
}
