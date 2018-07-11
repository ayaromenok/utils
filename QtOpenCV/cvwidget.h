#ifndef CVWIDGET_H
#define CVWIDGET_H

#include <QWidget>

class QCamera;
class QCameraImageCapture;
class QCameraViewfinder;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;

class CvWidget : public QWidget
{
    Q_OBJECT
public:
    CvWidget(QWidget *parent = nullptr);
    ~CvWidget();
signals:

public slots:

private:
    void                            _setCam();
    void                            _setMinUI();

    QCamera*                        _cam;
    QCameraImageCapture*            _imgCap;
    QCameraViewfinder*              _camViewFinder;
    QVBoxLayout*                    _vLOut;
    QHBoxLayout*                    _hLOut;
    QPushButton*                    _btnCapture;
    QLabel*                         _lblImgIn;
    QLabel*                         _lblImgOut;
    QLabel*                         _lblInfo;
};

#endif // CVWIDGET_H
