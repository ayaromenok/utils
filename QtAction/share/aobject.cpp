// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/utils/blob/master/LICENSE

#include "aobject.h"
#include "../share/share.h"


AObject::AObject(QObject *parent) : QObject(parent)
{
    YA_TIMESTAMP();
    _intVal = 0;
}

AObject::~AObject()
{
    YA_TIMESTAMP();
}


int
AObject::intVal()
{
    YA_TIMESTAMP();

    return _intVal;
}

void
AObject::setIntVal(int value)
{
    YA_TIMESTAMP();

    _intVal = value;
    qDebug() << "value" << _intVal;
}

bool
AObject::setIntValInvoke(int val)
{
    YA_TIMESTAMP();

    _intVal = val;
    qDebug() << "value" << _intVal;
    return true;
}
