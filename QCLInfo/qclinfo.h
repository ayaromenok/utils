#ifndef QCLINFO_H
#define QCLINFO_H

#include <QObject>
#include <QLoggingCategory>

#ifdef __APPLE__
    #include <OpenCL/cl.h>
#else
    #include <CL/cl.h>
#endif

Q_DECLARE_LOGGING_CATEGORY(clInfoMethodsFlow)
Q_DECLARE_LOGGING_CATEGORY(clInfoToConsole)

class QCLInfo : public QObject
{
    Q_OBJECT    

public:
    explicit QCLInfo(QObject *parent = nullptr);
    ~QCLInfo();
    QStringList getPlatformNames();
    QStringList getDeviceNames();

signals:

public slots:

private:
    void    getPlatforms();
    void    getDevices();

    cl_int      _status;
    cl_uint     _platformNum;
    cl_uint     _deviceNum;
    cl_uint     _deviceNumAll;
    QVector<cl_platform_id>     _platforms;
    QVector<cl_device_id>       _devices;
    QStringList                 _platformNames;
    QStringList                 _deviceNames;
};

#endif // QCLINFO_H
