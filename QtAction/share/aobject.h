// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/utils/blob/master/LICENSE

#ifndef QCVOBJECT_H
#define QCVOBJECT_H

#include <QObject>

class AObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int intVal READ intVal WRITE setIntVal NOTIFY intValChanged)
public:
    explicit AObject(QObject *parent = nullptr);
    ~AObject();

    Q_INVOKABLE bool setIntValInvoke(int val);

signals:
    void intValChanged(int);
public slots:
    int intVal();
    void setIntVal(int value);

private:
    int             _intVal;
};

#endif // QCVOBJECT_H
