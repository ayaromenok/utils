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
}
