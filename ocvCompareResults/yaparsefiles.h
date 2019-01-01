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
    void            parseFileList();
    void            parseFile(const QString &sFileName);
    void            addUniqueCvMethods(const QString &cvMethod);
    void            addUniqueClErrors(const QString &clError);
    void            addNotUniqueClErrors();
    void            dumpMethodsErrorsToFile(const QString sFileName = "out");
    QString*        _sArchDir;
    QStringList*    _slConfDirs;
    QStringList*    _slFileList;
    QStringList*    _slUniqueCvMethods;
    QStringList*    _slUniqueClErrors;
    QStringList*    _slNotUniqueClErrors;
    QVector<int>*   _vNotUniqueClErrorsCount;
};

#endif // YAPARSEFILES_H
