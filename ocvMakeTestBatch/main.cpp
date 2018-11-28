#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile fOut;
    QFile fIn;
    QString sFileIn;
    QString sFileOut;
    if (argc > 1)
    {
        sFileIn.append(argv[1]);
        qDebug() << "file: " << sFileIn;
        QFileInfo fi(sFileIn);
        if (fi.exists()){
            qDebug() << "size" << fi.size();
            fIn.setFileName(sFileIn);
            if (!fIn.open(QIODevice::ReadOnly | QIODevice::Text)){
                qDebug() << "can't open" << sFileIn << "to read";
                return -1;
            }
            sFileOut.append(sFileIn.left(sFileIn.length()-3));
            sFileOut.append("sh");
            qDebug() << "output to" << sFileOut;
            QTextStream in(&fIn);
            while (!in.atEnd()) {
                QString line = in.readLine();
                //process_line(line); //remove point from end of string
                qDebug() << line.left(line.length()-1);
            }

        } else {
            qDebug() << "file" << argv[1] << "missed";
        }
    }
    else {
        qDebug() << "file with test names required";
    }

    return a.exec();
}
