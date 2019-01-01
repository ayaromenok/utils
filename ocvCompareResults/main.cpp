#include <QCoreApplication>
#include <QDebug>
#include "yaparsefiles.h"

int main(int argc, char *argv[])
{
    YaParseFiles ypf;
    QString sArchDir;
    if (argc > 1)
    {
        sArchDir.append(argv[1]);
    }
    ypf.addArchDir(sArchDir);

    return 0;
}
