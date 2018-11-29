#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile fOut;
    QFile fIn;
    QString sFileIn;
    QString sFileOut("run_");
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

            QTextStream in(&fIn);
            QString sTestName("opencv_");
            sTestName.append(sFileIn.left(sFileIn.length()-4));
            qDebug() << "test name" << sTestName;
            fOut.setFileName(sFileOut);
            if (!fOut.open((QIODevice::WriteOnly|QIODevice::Text))){
                qDebug() << "can't open" << sFileOut << "to write";
                return -1;
            } else {
                qDebug() << "write to" << sFileOut;
            }
            QTextStream out(&fOut);
            out << "#!/bin/sh\n";
            out << "mkdir res\n" ;
            out << "echo \"\n\nrunning:\t\t" << sTestName << "\n\n\"\n";
            while (!in.atEnd()) {
                QString sLine = in.readLine();
                //some tests have DISABLED in name - disable it here too?
                QString sLineOut("echo \"");
                sLine = sLine.left(sLine.length()-1);
                //qDebug() << sLine;
                sLineOut.append(sLine);
                sLineOut.append("\"\ntime -p ./");
                sLineOut.append(sTestName);
                sLineOut.append(" --gtest_filter=*");
                sLineOut.append(sLine);
                sLineOut.append("* > res/");
                sLineOut.append(sTestName);
                sLineOut.append("_");
                //some test names include '/' and space
                sLineOut.append(sLine.replace("/","_").remove(" "));
                sLineOut.append(".txt\n");
                //qDebug() << sLineOut;
                out << sLineOut ;
            }
            fIn.close();
            fOut.flush();
            fOut.close();

        } else {
            qDebug() << "file" << argv[1] << "missed";
        }
    }
    else {
        qDebug() << "file with test names required";
        qDebug() << "to obtain it use something like:";
        qDebug() << "./opencv_perf_stitching --gtest_list_tests --gtest_filter=*OCL* | grep OCL_ > perf_stitching.txt";

    }

    return 0;
}
