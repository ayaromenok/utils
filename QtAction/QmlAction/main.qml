// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/utils/blob/master/LICENSE

import QtQuick 2.9 as QQ
import QtQuick.Window 2.9
import QtQuick.Layouts 1.1 as QQL
import QtQuick.Controls 2.2 as QQC
import QtQuick.Controls 1.4 as QQC1

import AObject 1.0

Window {
    visible: true
    width: 360
    height: 600
    title: qsTr("Qt Quick for OpenCV")

    AObject{
        id:ao
    }
    QQC1.Action {
        id: acExit
        text: "E&xit"
        //shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
    }

    QQC1.Action {
        id: acInvoke
        text: "Invoke"
        //shortcut: StandardKey.Quit
        onTriggered: ao.setIntValInvoke(10)
    }
    QQC1.Action {
        id: acSetInterval
        text: "SetInterval"
        //shortcut: StandardKey.Quit
        onTriggered: ao.setIntVal(10)
    }


    QQL.GridLayout {
        anchors.fill: parent
        rows:4
        columns:1
        QQ.Rectangle{
            color: "grey"
            implicitHeight: 360
            implicitWidth: 360
            QQL.ColumnLayout{
                QQC1.ToolBar{
                    QQL.RowLayout {
                        QQC1. ToolButton {
                            action: acInvoke
                        }
                        QQC1. ToolButton {
                            action: acSetInterval
                        }
                        QQC1. ToolButton {
                            action: acExit
                        }
                    }
                }
                //Quick 2.x
                QQC.Button{
                    text: "setIntValue/Invoke"
                    onPressed: { ao.setIntValInvoke(10)
                        }
                }
                QQC.Button{
                    text: "setIntValue/Property"
                    onPressed: { ao.setIntVal(4)
                        }
                }
                //Quick 1.x
                QQC1.Button {
                    action: acInvoke
                }
                QQC1.Button {
                    action: acSetInterval
                }
                QQC1.Button{
                    action: acExit
                }
            }
        }

    }
}
