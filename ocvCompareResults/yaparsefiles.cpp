#include "yaparsefiles.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>

YaParseFiles::YaParseFiles(QObject *parent) : QObject(parent)
{

}

YaParseFiles::~YaParseFiles()
{

}

void
YaParseFiles::addArchDir(QString &sArchDir)
{
    _sArchDir = new QString;
    if (sArchDir.length() > 0){
        _sArchDir->append(sArchDir);
        qInfo() << "use arch dir value:" << _sArchDir->toLatin1();
    } else {
        _sArchDir->append("Rk3399");
        qWarning() << "use default arch dir value:" << _sArchDir->toLatin1();
    }
    addConfDirs();
    addFileList();
    parseFileList();
}

void
YaParseFiles::addConfDirs()
{
    QDir dir;
    _slConfDirs = new QStringList;
    if (!dir.cd(_sArchDir->toLatin1())){
        qWarning() << "dir" << _sArchDir->toLatin1() << "not exist, exiting";
        return;
    }
    _slConfDirs->append(dir.entryList(QDir::Dirs|QDir::NoDot|QDir::NoDotDot));
    qDebug() << "dirs:" << _slConfDirs->length() << _slConfDirs->toVector();
}

void
YaParseFiles::addFileList()
{
    QDir dir;
    _slFileList = new QStringList;
    dir.cd(_sArchDir->toLatin1());
    for (int i=0; i<_slConfDirs->length(); i++){
        if (dir.cd(_slConfDirs->at(i))){
            QStringList fileList = dir.entryList(QDir::Files);
            if (fileList.length() >0 ){
                for (int j=0; j<fileList.length(); j++){
                    fileList[j].insert(0,"/");
                    fileList[j].insert(0,dir.canonicalPath());
                }
                _slFileList->append(fileList);
            } else {
                qWarning() << "empty dir" << dir.currentPath();
            }
            dir.cdUp();
        }
        else {
            qWarning() << "can't cd to" << _slConfDirs->at(i);
        }
    }
    //qDebug() << "files" << _slFileList;
}

void
YaParseFiles::parseFileList()
{
    if (_slFileList->length() > 0){
        for (int i=0; i<_slFileList->length(); i++){
            //qDebug() << i << _slFileList->at(i);
            parseFile(_slFileList->at(i));
        }
    } else {
        qWarning() << "no file to parse";
    }
}

void
YaParseFiles::parseFile(const QString &sFileName)
{
    QFileInfo fi(sFileName);
    QFile fileIn;
    if (fi.exists()){
        qDebug() << "file" << sFileName << ", size" << fi.size();
        fileIn.setFileName(sFileName);
        if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text)){
            qWarning() << "can't open" << sFileName << "to read";
            return;
        }
        QTextStream streamIn(&fileIn);
        int countClOutOfRes = 0;
        QString sTestName;
        QStringList slTestCLError;
        while (!streamIn.atEnd()) {
            QString sLine = streamIn.readLine();
            if (sLine.contains("[ RUN      ]")){
                //qDebug() << "line" << sLine;
                //qDebug() << "test name" << sLine.right(sLine.length() -13);
                if (countClOutOfRes==0){
                    sTestName.clear();
                    sTestName.append(sLine.right(sLine.length() -13));
                }
                if (!streamIn.atEnd()){
                    QString sLineNext = streamIn.readLine();
                    if (sLineNext.contains("[       OK ]")){
                        QString res = sLineNext.left(sLineNext.indexOf(" ms"));
                        res = res.right(res.length()-res.indexOf("(")-1);
                        //qDebug() << "OK" << res.toInt() << "msec";
                    } else if (sLineNext.contains("[ PERFSTAT ]")){
                        //qDebug() << "PERF" << sLineN;
                    } else if (sLineNext.contains("CL_OUT_OF_RES")){
                        //qDebug() << "CL out_of_res" << sLineN;
                        countClOutOfRes++;
                        if (slTestCLError.isEmpty()){
                            slTestCLError.append(sLineNext);
                        } else if (!slTestCLError.last().contains(sLineNext)){
                            slTestCLError.append(sLineNext);
                        }
                    }
                }
            } else if (sLine.contains("CL_OUT_OF_RES")){
                //qDebug() << "CL out_of_res" << sLine;
                countClOutOfRes++;
            } else if (sLine.contains("[       OK ]")){
                if (countClOutOfRes>0){
                    qDebug() << "Test name:" << sTestName;
                    qDebug() << slTestCLError;
                    qDebug() << "Total # of CL errors:" << countClOutOfRes;
                    sTestName.clear();
                    slTestCLError.clear();
                    countClOutOfRes = 0;
                }
                //qDebug() << "NOK, see CL errors above";// << sLine;
            }
        }
    } else {
        qWarning() << "file" << sFileName << "not found";
    }
}
