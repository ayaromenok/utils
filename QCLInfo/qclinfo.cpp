#include "qclinfo.h"
#include <QDebug>

Q_LOGGING_CATEGORY(clInfoMethodsFlow, "clInfo.Methods.Flow")
Q_LOGGING_CATEGORY(clInfoToConsole, "clInfo.To.Console")

QCLInfo::QCLInfo(QObject *parent) : QObject(parent)
{    
    qCInfo(clInfoMethodsFlow) << "QCLInfo::QCLInfo()";
    _platformNum = 0;
    _deviceNum = 0;
    _deviceNumAll = 0;
    getPlatforms();
    getDevices();
}

QCLInfo::~QCLInfo()
{
    qCInfo(clInfoMethodsFlow) << "QCLInfo::~QCLInfo()";
}

QStringList
QCLInfo::getPlatformNames()
{
    qCInfo(clInfoMethodsFlow) << "QCLInfo::getPlatformNames()";
    getPlatforms();
    return _platformNames;
}

QStringList
QCLInfo::getDeviceNames()
{
    qCInfo(clInfoMethodsFlow) << "QCLInfo::getDeviceNames()";
    if (_platformNum == 0)
        getPlatforms();
    getDevices();
    return _deviceNames;
}

void
QCLInfo::getPlatforms(){
    size_t bSize;

    qCInfo(clInfoMethodsFlow)  << "QCLInfo::getPlatforms()";

    _platformNames.clear();

    _status = clGetPlatformIDs(0, NULL, &_platformNum);

    if (CL_SUCCESS != _status) {
        qCritical() << "clGetPlatformIDs/platforms number failed";
        exit(0);
    } else {
        qCInfo(clInfoToConsole) << "platformNum:" << _platformNum;
    }

    _platforms.resize(_platformNum);
    _status = clGetPlatformIDs(_platformNum,_platforms.data(), NULL);
    if (CL_SUCCESS != _status) {
        qCritical() << "clGetPlatformIDs/platforms list failed";
        exit(0);
    } else {
        qCInfo(clInfoToConsole) << "platformList:" << _platforms;
    }

    for (unsigned int i=0; i<_platformNum; ++i){

        _status = clGetPlatformInfo(_platforms.at(i), CL_PLATFORM_NAME, 0, NULL,
                                    &bSize);
        if (CL_SUCCESS != _status){
            qCritical() << "clGetPlatformInfo/size of platform name failed";
            exit(0);
        }else {
            qCInfo(clInfoToConsole) << "platform" << i << "name lengths: "
                                    << bSize;
        }

        QByteArray platformName((int)bSize, ' ');
        _status = clGetPlatformInfo(_platforms.at(i), CL_PLATFORM_NAME, bSize,
                                    platformName.data(), NULL);
        if (CL_SUCCESS != _status){
            qCritical() << "clGetPlatformInfo/name of platform failed";
            exit(0);
        }else {
            qCInfo(clInfoToConsole) << "platform" << i << "name: "
                                    << platformName;
            _platformNames.append(QString(platformName));
        }
    }
}

void
QCLInfo::getDevices(){
    size_t bSize;
    _deviceNumAll = 0;

    qCInfo(clInfoMethodsFlow)  << "QCLInfo::getDevices()";

    _deviceNames.clear();

    for (unsigned int i=0; i<_platformNum; ++i){
        QVector<cl_device_id>       devicesOnPlatform;
        _deviceNum = 0;
        _status = clGetDeviceIDs(_platforms.at(i), CL_DEVICE_TYPE_ALL, 0, NULL,
                                    &_deviceNum);
        if (CL_SUCCESS != _status) {
            qCritical() << "clGetDeviceIDs/device number failed at "
                        << _platformNames.at(i);
            exit(0);
        } else {
            qCInfo(clInfoToConsole) << "at platform:" << _platformNames.at(i)
                                    << "device num" << _deviceNum;
            _deviceNumAll += _deviceNum;
        }

        devicesOnPlatform.resize(_deviceNum);
        _status = clGetDeviceIDs(_platforms.at(i),CL_DEVICE_TYPE_ALL, _deviceNum,
                                devicesOnPlatform.data(), NULL);
        if (CL_SUCCESS != _status) {
            qCritical() << "clGetDevicesIDs/devices list failed at "
                           << _platformNames.at(i);
            exit(0);
        } else {
            qCInfo(clInfoToConsole) << "deviceList:" << devicesOnPlatform;
            _devices.append(devicesOnPlatform);
        }

        for (unsigned int j=0; j<_deviceNum; ++j){

            _status = clGetDeviceInfo(devicesOnPlatform.at(j), CL_DEVICE_NAME,
                                      0, NULL, &bSize);
            if (CL_SUCCESS != _status){
                qCritical() << "clGetDeviceInfo/size of device name failed";
                exit(0);
            }else {
                qCInfo(clInfoToConsole) << "device" << j << "name lengths: "
                                        << bSize;
            }

            QByteArray deviceName((int)bSize, ' ');
            _status = clGetDeviceInfo(devicesOnPlatform.at(j), CL_DEVICE_NAME,
                                      bSize, deviceName.data(), NULL);
            if (CL_SUCCESS != _status){
                qCritical() << "clGetDeviceInfo/name of device failed";
                exit(0);
            }else {
                qCInfo(clInfoToConsole) << "device" << j << "name: "
                                        << deviceName;
                _deviceNames.append(QString(deviceName));
            }
        }
    }
}

cl_platform_id
QCLInfo::getPlatform()
{
    if (_platformNum > 0)
        return _platforms.at(0);
    return 0;
}

cl_device_id
QCLInfo::getDeviceId()
{
    if (_deviceNum > 0)
        return _devices.at(0);
    return 0;
}
