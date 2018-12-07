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
    _vslFileList = new QVector<QStringList>;
    dir.cd(_sArchDir->toLatin1());
    for (int i=0; i<_slConfDirs->length(); i++){
        if (dir.cd(_slConfDirs->at(i))){
            _vslFileList->append(dir.entryList(QDir::Files));
            dir.cdUp();
        }
        else {
            qWarning() << "can't cd to" << _slConfDirs->at(i);
        }
    }
    qDebug() << "files" << _vslFileList->toList();
}
