#ifndef YAPARSEFILES_H
#define YAPARSEFILES_H

#include <QObject>

class YaParseFiles : public QObject
{
    Q_OBJECT
public:
    explicit YaParseFiles(QObject *parent = nullptr);
    ~YaParseFiles();
    void addArchDir(QString & sArchDir);
signals:

public slots:

private:
    void            addConfDirs();
    void            addFileList();
    QString*        _sArchDir;
    QStringList*    _slConfDirs;
    QVector<QStringList>* _vslFileList;
};

#endif // YAPARSEFILES_H
