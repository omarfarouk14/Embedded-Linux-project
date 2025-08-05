import QtQuick 2.15

Rectangle {
    id: root
    width: 400
    height: 300
    color: "transparent"

    // Background image
    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "qrc:/icons/Resources/icons/background.jpg"
        opacity: 1.0   // must be between 0.0 and 1.0
    }

    // Optional gradient overlay for better contrast (can be removed)
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 1.0; color: "#40000000" }
        }
    }

    // Main content container (smaller now)
    Rectangle {
        id: meterContainer
        anchors.centerIn: parent
        width: 220     // Reduced width
        height: 150    // Reduced height
        color: "#E0FFFFFF"
        border.color: "#333333"
        border.width: 2
        radius: 12

        Column {
            anchors.centerIn: parent
            spacing: 12

            Text {
                text: "Temperature"
                font.pixelSize: 22
                font.bold: true
                color: "#333333"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                id: temperatureValue
                text: currentTemperature.toFixed(2) + "°C"
                font.pixelSize: 28
                font.bold: true
                color: currentTemperature > 30 ? "#FF4444" : "#0066CC"
                anchors.horizontalCenter: parent.horizontalCenter

                Behavior on color {
                    ColorAnimation { duration: 300 }
                }
            }

            Rectangle {
                width: 160
                height: 16
                color: "#DDDDDD"
                border.color: "#999999"
                border.width: 1
                radius: 8
                anchors.horizontalCenter: parent.horizontalCenter

                Rectangle {
                    id: temperatureIndicator
                    width: Math.min(parent.width * (currentTemperature / 50), parent.width)
                    height: parent.height
                    color: currentTemperature > 30 ? "#FF4444" : "#44AA44"
                    radius: parent.radius

                    Behavior on width {
                        NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                    }
                    Behavior on color {
                        ColorAnimation { duration: 300 }
                    }
                }
            }
        }
    }
}
