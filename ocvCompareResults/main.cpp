#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "yaparsefiles.h"

int parseFile(QString &sFileName){
    QFileInfo fi(sFileName);
    QFile fileIn;
    if (fi.exists()){
        qDebug() << "file" << sFileName << ", size" << fi.size();
        fileIn.setFileName(sFileName);
        if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text)){
            qWarning() << "can't open" << sFileName << "to read";
            return -1;
        }
        QTextStream streamIn(&fileIn);
        int countClOutOfRes = 0;
        while (!streamIn.atEnd()) {
            QString sLine = streamIn.readLine();

            if (sLine.contains("[ RUN      ]")){

                //qDebug() << "line" << sLine;
                qDebug() << "test name" << sLine.right(sLine.length() -13);
                if (!streamIn.atEnd()){
                    QString sLineN = streamIn.readLine();
                    if (sLineN.contains("[       OK ]")){
                        QString res = sLineN.left(sLineN.indexOf(" ms"));
                        res = res.right(res.length()-res.indexOf("(")-1);
                        qDebug() << "OK" << res.toInt() << "msec";

                    } else if (sLineN.contains("[ PERFSTAT ]")){
                        qDebug() << "PERF" << sLineN;
                    } else if (sLineN.contains("CL_OUT_OF_RES")){
                        qDebug() << "CL out_of_res" << sLineN;
                        countClOutOfRes++;
                    }
                }
            } else if (sLine.contains("CL_OUT_OF_RES")){
                //qDebug() << "CL out_of_res" << sLine;
                countClOutOfRes++;
            }else if (sLine.contains("[       OK ]")){
                if (countClOutOfRes>0){
                    qDebug() << "Total # of CL errors:" << countClOutOfRes;
                    countClOutOfRes = 0;
                }
                qDebug() << "NOK, see CL errors above";// << sLine;
            }
        }

    } else {
        qWarning() << "file" << sFileName << "not found";
    }
    return 0;
}

int parseFileList(QVector<QStringList> &fileList){
    for (int i=0; i<fileList.length(); i++){
        qDebug() <<fileList.at(i);
        QStringList list = fileList.at(i);
        if (list.length()>2) {
            for (int j=2; j<list.length();j++){
                QString sFileName(list.at(0));
                sFileName.append('/');
                sFileName.append(list.at(1));
                sFileName.append('/');
                sFileName.append(list.at(j));
                parseFile(sFileName);
            }
        } else
        {
            qWarning() << "File list is not correct, exiting";
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    YaParseFiles ypf;
    QString sArchDir;
    if (argc > 1)
    {
        sArchDir.append(argv[1]);
    }
    ypf.addArchDir(sArchDir);


//    QDir dir;
//    QStringList dirList;
//    QString dirArch;
//    QVector<QStringList> testFileList;
//    QCoreApplication a(argc, argv);
//    qDebug() << "Compare results from opencv_perf/test ";
//    qDebug() << "run at" << QDir::current();
//    if (argc > 1)
//    {
//        qDebug() << "arch dir:" << argv[1];
//        dirArch.append(argv[1]);
//    } else {
//        qDebug() << "no arch dir selected, use default: Rk3399";
//        dirArch.append("Rk3399");
//    }

//    dir.cd(dirArch);
//    dirList = dir.entryList();

//    // dirList start with current dir(".") and upper dir(".."), so drop them
//    for (int i=2; i< dirList.length(); i++){
//        dir.cd(dirList.at(i));
//        QStringList list = dir.entryList(QDir::Files);
//        //store arch as first element and testdir as second;
//        list.insert(0,dirList.at(i));
//        list.insert(0,dirArch);
//        testFileList.append(list);
//        dir.cdUp();
//    }
//    parseFileList(testFileList);
    return 0;
}
