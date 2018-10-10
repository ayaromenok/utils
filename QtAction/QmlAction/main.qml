// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

import QtQuick 2.9 as QQ
import QtQuick.Window 2.9
import QtQuick.Layouts 1.1 as QQL
import QtQuick.Controls 2.2 as QQC
import QtMultimedia 5.9 as QMM

import AObject 1.0

Window {
    visible: true
    width: 360
    height: 600
    title: qsTr("Qt Quick for OpenCV")

    AObject{
        id:ao
    }

    QQL.GridLayout {
        anchors.fill: parent
        rows:4
        columns:1
        QQ.Rectangle{
            color: "grey"
            implicitHeight: 200
            implicitWidth: 360
            QQL.ColumnLayout{
                QQC.Button{
                    text: "setIntValue/Invoke"
                    onPressed: { ao.setIntValIvoke(10)
                        }
                }
                QQC.Button{
                    text: "setIntValue/Property"
                    onPressed: { ao.setIntVal(4)
                        }
                }
            }
        }

    }
}
