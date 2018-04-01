import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtSensors 5.10

Window {
    visible: true
    width: 360
    height: 640
    title: qsTr("SensorTest")

    TiltSensor {
        id: tilt
        active: true
    }
    RotationSensor{
        id: rotation
        active: true
    }
    PressureSensor{
        id: pressure
        active: true
    }
    Altimeter{
        id:altimeter
        active:true
    }
    Accelerometer{
        id: accel
        active:true
    }
    Compass{
        id: compass
        active:true
    }
    // UI
    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            implicitWidth: parent.width
            implicitHeight: 90
            GroupBox {
                id: gbTilt
                font.bold: true
                font.pointSize: 13
                anchors.fill: parent
                title: "Tilt"

                RowLayout {
                    anchors.fill: parent
                    Button {
                        id: tiltStart
                        text: tilt.active ? "Stop" : "Start"
                        onClicked: {
                            tilt.active = (tiltStart.text === "Start");
                        }
                    }
                    Text {
                        id: tiltXtext
                        verticalAlignment: Text.AlignVCenter
                        text: "X: " + (tilt.reading ? tilt.reading.xRotation.toFixed(2) + "°" : "--")
                    }
                    Text {
                        id: tiltYtext
                        verticalAlignment: Text.AlignVCenter
                        text: "Y: " + (tilt.reading ? tilt.reading.yRotation.toFixed(2) + "°" : "--")
                    }
                }
            }
        }
        Rectangle{
            implicitWidth: parent.width
            implicitHeight: 90
            GroupBox {
                id: gbRotation
                font.bold: true
                font.pointSize: 13
                anchors.fill: parent
                title: "Rotation"
                RowLayout {
                    anchors.fill: parent
                    Button {
                        id: rotationStart
                        text: rotation.active ? "Stop" : "Start"
                        onClicked: {
                            rotation.active = (rotationStart.text === "Start");
                        }
                    }
                    Text {
                        id: rotXtext
                        verticalAlignment: Text.AlignVCenter
                        text: "X: " + (rotation.reading ? rotation.reading.x.toFixed(2) + "°" : "--")
                    }
                    Text {
                        id: rotYtext
                        verticalAlignment: Text.AlignVCenter
                        text: "Y: " + (rotation.reading ? rotation.reading.y.toFixed(2) + "°" : "--")
                    }
                    Text {
                        id: rotZtext
                        verticalAlignment: Text.AlignVCenter
                        text: "Z: " + (rotation.reading ? rotation.reading.z.toFixed(2) + "°" : "--")
                    }
                }
            }
        }

        Rectangle{
            implicitWidth: parent.width
            implicitHeight: 90
            GroupBox {
                id: gbPressuer
                font.bold: true
                font.pointSize: 13
                anchors.fill: parent
                title: "Pressute/Temperature"

                RowLayout {
                    anchors.fill: parent
                    Button {
                        id: pressureStart
                        text: pressure.active ? "Stop" : "Start"
                        onClicked: {
                            pressure.active = (pressureStart.text === "Start");
                        }
                    }
                    Text {
                        id: pressureText
                        verticalAlignment: Text.AlignVCenter
                        text: "Pressure: " + (pressure.reading ? (pressure.reading.pressure/100).toFixed(2) + "hPa" : "--")
                    }
                    Text {
                        id: temperatureText
                        verticalAlignment: Text.AlignVCenter
                        text: "Temperature: " + (pressure.reading ? pressure.reading.temperature.toFixed(2) + "°" : "--")
                    }
                }
            }
        }

        Rectangle{
            implicitWidth: parent.width
            implicitHeight: 90
            GroupBox {
                id: gbAltimeter
                anchors.fill: parent
                font.bold: true
                font.pointSize: 13
                title: "Altimeter"

                RowLayout {
                    anchors.fill: parent
                    Button {
                        id: altimeterStart
                        text: altimeter.active ? "Stop" : "Start"
                        onClicked: {
                            altimeter.active = (altimeterStart.text === "Start");
                        }
                    }
                    Text {
                        id: altimeterText
                        verticalAlignment: Text.AlignVCenter
                        text: "Altitude: " + (altimeter.reading ? altimeter.reading.altitude.toFixed(2) + "meters" : "--")
                    }
                }
            }
        }
        Rectangle{
            implicitWidth: parent.width
            implicitHeight: 90
            GroupBox {
                id: gbAccel
                anchors.fill: parent
                font.bold: true
                font.pointSize: 13
                title: "Acceleration"

                RowLayout {
                    anchors.fill: parent
                    Button {
                        id: accelStart
                        text: accel.active ? "Stop" : "Start"
                        onClicked: {
                            accel.active = (accelStart.text === "Start");
                        }
                    }
                    Text {
                        id: accelXtext
                        verticalAlignment: Text.AlignVCenter
                        text: "X: " + (accel.reading ? accel.reading.x.toFixed(2) + " m/s^2" : "--")
                    }
                    Text {
                        id: accelYtext
                        verticalAlignment: Text.AlignVCenter
                        text: "Y: " + (accel.reading ? accel.reading.y.toFixed(2) + " m/s^2" : "--")
                    }
                    Text {
                        id: accelZtext
                        verticalAlignment: Text.AlignVCenter
                        text: "Z: " + (accel.reading ? accel.reading.z.toFixed(2) + " m/s^2" : "--")
                    }
                }
            }
        }
        Rectangle{
            implicitWidth: parent.width
            implicitHeight: 90
            GroupBox {
                id: gbCompass
                anchors.fill: parent
                font.bold: true
                font.pointSize: 13
                title: "Compass"
                RowLayout {
                    anchors.fill: parent
                    Button {
                        id: compassStart
                        text: compass.active ? "Stop" : "Start"
                        onClicked: {
                            compass.active = (compassStart.text === "Start");
                        }
                    }
                    Text {
                        id: azimuthText
                        verticalAlignment: Text.AlignVCenter
                        text: "Azimuth: " + (compass.reading ? compass.reading.azimuth.toFixed(2) + "°" : "--")
                    }
                    Text {
                        id: compassCalibrationText
                        verticalAlignment: Text.AlignVCenter
                        text: "Cal Level: " + (compass.reading ? compass.reading.calibrationLevel.toFixed(2) + "%" : "--")
                    }
                }

            }
        }
        Rectangle{
            implicitWidth: parent.width
            implicitHeight: 360
        }

    }//ColumnLayout
}
