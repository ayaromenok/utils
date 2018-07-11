#include "cvwidget.h"
#include <QDebug>
#include <QDateTime>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <opencv/cv.hpp>

CvWidget::CvWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::CvWidget()";
    _setMinUI();
    _setCam();
}

CvWidget::~CvWidget()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::~CvWidget()";
    if (_cam)
        delete _cam;
}

void
CvWidget::_setCam()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::_setCam()";
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        qDebug() << "camera: " << cameraInfo.description();
    }
    _cam = new QCamera(QCameraInfo::defaultCamera());
    _cam->setCaptureMode(QCamera::CaptureStillImage);

    _imgCap = new QCameraImageCapture(_cam);
    _imgCap->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
   connect(_imgCap, &QCameraImageCapture::imageAvailable,
           this, &CvWidget::_imgToBuffer);
   connect(_btnCapture, SIGNAL(pressed()),
                               this, SLOT (_imgCapture()));

    _camViewFinder->show();
    _cam->setViewfinder(_camViewFinder);
    _cam->start();
}

void
CvWidget::_setMinUI()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::_setMinUI()";
    this->setWindowTitle("Qt\OpenCV camera");
    this->setGeometry(0, 0, 360, 720);

    QImage cvLogo = QImage(":/res/opencvlogo320x240.png");

    _vLOut = new QVBoxLayout();
    _hLOut = new QHBoxLayout();
    _lblInfo = new QLabel("info");
    _lblImgIn = new QLabel("image from Camera");
    _lblImgIn->setPixmap(QPixmap::fromImage(cvLogo));
    _lblImgOut = new QLabel("image from OpenCV");
    _lblImgOut->setPixmap(QPixmap::fromImage(cvLogo));
    _btnCapture = new QPushButton("capture");
    _camViewFinder = new QCameraViewfinder();
    _hLOut->addWidget(_btnCapture);
    _hLOut->addWidget(_lblInfo);
    _vLOut->addLayout(_hLOut);
    _vLOut->addWidget(_camViewFinder);
    _vLOut->addWidget(_lblImgIn);
    _vLOut->addWidget(_lblImgOut);

    this->setLayout(_vLOut);
}

void
CvWidget::_imgCapture()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::_imgCapture()";
    _cam->searchAndLock();
    _imgCap->capture();
    _cam->unlock();
}

void
CvWidget::_imgToBuffer(int id, const QVideoFrame &buffer)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::_imgToBuffer("
             << id << "," << buffer.size() << ")";
    _lblInfo->setText("Image #"+QString::number(id)+" captured");   QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(
                frame.pixelFormat());
    int nbytes = frame.mappedBytes();
    QImage imgIn = QImage::fromData(frame.bits(), nbytes).scaledToWidth(360);
    qDebug() << "imgIn format" << imgIn.format() << "// 4 - Image::Format_RGB32";
    _lblImgIn->setPixmap(QPixmap::fromImage(imgIn));
    _cvStubRgb2GrayEdge(imgIn);
    //_cvStubRgbBlur(imgIn);
}

void
CvWidget::_cvStubRgb2GrayEdge(QImage & image)
{
    qint64 startTime, endTime, difTime;
    startTime = QDateTime::currentMSecsSinceEpoch();

    cv::Mat cvIn(cv::Size(image.width(), image.height()),
                          CV_8UC4, image.bits()); //image from camera 32bit alligned
    cv::Mat cvTmpGray;
    cv::cvtColor(cvIn, cvTmpGray, cv::COLOR_RGBA2GRAY);

    cv::Mat cvTmpCanny;
    cv::Canny(cvTmpGray, cvTmpCanny, 10, 100, 3, true);

#ifdef DEBUG_PC_IMSHOW
    // while OpenCV build with Qt on PC, it's possible to mix native Qt window
    // with separate cv::NamedWindow for displaying immidiate result
    // but it's crashed on Android/other due to single-window architecture
    cv::namedWindow("cvTmpGray", cv::WINDOW_AUTOSIZE);
    cv::imshow("cvTmpGray", cvTmpGray);

    cv::namedWindow("cvTmpCanny", cv::WINDOW_AUTOSIZE);
    cv::imshow("cvTmpCanny", cvTmpCanny);
#endif //DEBUG_PC_IMSHOW

    QImage imgOut(image.width(), image.height(), QImage::Format_RGB888);
    cv::Mat cvOut(cv::Size(imgOut.width(),imgOut.height()),
                  CV_8UC3, imgOut.bits());
    cv::cvtColor(cvTmpCanny, cvOut, cv::COLOR_GRAY2RGB);

    endTime = QDateTime::currentMSecsSinceEpoch();
    difTime = endTime-startTime;
    qDebug() << startTime << "CvWidget::_cvStubRgb2GrayEdge(" << image.size() << ")";
    qDebug() << endTime << "duration:" << difTime << "msec";
    _lblImgOut->setPixmap(QPixmap::fromImage(imgOut));
}

void
CvWidget::_cvStubRgbBlur(QImage & image)
{
    qint64 startTime, endTime, difTime;
    startTime = QDateTime::currentMSecsSinceEpoch();

    cv::Mat cvIn(cv::Size(image.width(), image.height()),
                          CV_8UC4, image.bits()); //image from camera 32bit alligned
    cv::Mat cvTmp;
    cv::cvtColor(cvIn, cvTmp, cv::COLOR_RGBA2RGB);

    cv::Mat cvTmpBlur;
    cv::GaussianBlur(cvTmp, cvTmpBlur, cv::Size(5,5), 3, 3);

#ifdef DEBUG_PC_IMSHOW
    // while OpenCV build with Qt on PC, it's possible to mix native Qt window
    // with separate cv::NamedWindow for displaying immidiate result
    // but it's crashed on Android/other due to single-window architecture
    cv::namedWindow("cvTmp", cv::WINDOW_AUTOSIZE);
    cv::imshow("cvTmp", cvTmp);

    cv::namedWindow("cvTmpBlur", cv::WINDOW_AUTOSIZE);
    cv::imshow("cvTmpBlur", cvTmpBlur);
#endif //DEBUG_PC_IMSHOW

    QImage imgOut(image.width(), image.height(), QImage::Format_RGB888);
    cv::Mat cvOut(cv::Size(imgOut.width(),imgOut.height()),
                  CV_8UC3, imgOut.bits());
    cv::cvtColor(cvTmpBlur, cvOut, cv::COLOR_BGR2RGB);

    endTime = QDateTime::currentMSecsSinceEpoch();
    difTime = endTime-startTime;
    qDebug() << startTime << "CvWidget::_cvStubRgbBlur(" << image.size() << ")";
    qDebug() << endTime << "duration:" << difTime << "msec";
    _lblImgOut->setPixmap(QPixmap::fromImage(imgOut));
}
