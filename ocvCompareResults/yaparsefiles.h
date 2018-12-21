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
    void            addUniqueCvMethod(const QString &cvMethod);
    void            addUniqueClError(const QString &clError);
    void            dumpMethodsErrorsToFile(const QString sFileName = "out");
    QString*        _sArchDir;
    QStringList*    _slConfDirs;
    QStringList*    _slFileList;
    QStringList*    _slUniqueClErrors;
    QStringList*    _slUniqueCvMethods;
};

#endif // YAPARSEFILES_H
