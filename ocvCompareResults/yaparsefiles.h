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
    QString*        _sArchDir;
    QStringList*    _slConfDirs;
};

#endif // YAPARSEFILES_H
