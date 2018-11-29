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
            qDebug() << "output to" << sFileOut;
            QTextStream in(&fIn);
            QString sTestName("opencv_");
            sTestName.append(sFileIn.left(sFileIn.length()-4));
            qDebug() << "test name" << sTestName;
            sFileOut.append("sTestName");
            sFileOut.append(".sh");
            fOut.setFileName(sFileOut);
            if (!fOut.open((QIODevice::WriteOnly|QIODevice::Text))){
                qDebug() << "can't open" << sFileOut << "to write";
                return -1;
            } else {
                qDebug() << "write to" << sFileOut;
            }
            QTextStream out(&fOut);
            while (!in.atEnd()) {
                QString sLine = in.readLine();
                QString sLineOut("echo \"");
//                echo "OCL_DilateFixture_Dilate"
//                time ./opencv_perf_imgproc --gtest_filter=*OCL_DilateFixture_Dilate* > perf_imgproc_OCL_DilateFixture_Dilate.txt
                //process_line(line); //remove point from end of string
                sLine = sLine.left(sLine.length()-1);
                qDebug() << sLine;
                sLineOut.append(sLine);
                sLineOut.append("\"\ntime ./");
                sLineOut.append(sTestName);
                sLineOut.append(" --gtest_filter=*");
                sLineOut.append(sLine);
                sLineOut.append("* > ");
                sLineOut.append(sTestName);
                sLineOut.append("_");
                sLineOut.append(sLine);
                sLineOut.append(".txt\n");
                qDebug() << sLineOut;
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
    }

    return a.exec();
}
