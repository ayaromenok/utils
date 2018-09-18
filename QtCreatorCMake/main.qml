// main.qml
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Label {
        text: qsTr("Android CMake Test")
        anchors.centerIn: parent
    }
}

