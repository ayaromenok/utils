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

    _camViewFinder->show();
    _cam->setViewfinder(_camViewFinder);
    _cam->start();
}

void
CvWidget::_setMinUI()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::_setMinUI()";
    this->setWindowTitle("Qt\OpenCV camera");
    this->setGeometry(0, 0, 360, 640);

    _vLOut = new QVBoxLayout();
    _hLOut = new QHBoxLayout();
    _lblInfo = new QLabel("info");
    _lblImgIn = new QLabel("image from Camera");
    _lblImgOut = new QLabel("image from OpenCV");
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
