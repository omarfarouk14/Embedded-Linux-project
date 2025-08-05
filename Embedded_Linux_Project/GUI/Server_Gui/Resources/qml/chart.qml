import QtQuick 2.15
import QtCharts 2.15

Rectangle {
    id: root
    anchors.fill: parent

    // Properties for scroll behavior
    property real scrollPosition: 0
    property real maxScrollPosition: 0
    property bool autoScroll: true
    property int visibleDataPoints: 50
    property real scrollSensitivity: 1.0

    // Background image
    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "qrc:/icons/Resources/icons/background.jpg"
        opacity: 1.0   // must be between 0.0 and 1.0
    }

    // Professional gradient background
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#f0f8ff" }
        GradientStop { position: 1.0; color: "#e6f3ff" }
    }

    // Optional: Add subtle pattern overlay
    Rectangle {
        anchors.fill: parent
        opacity: 0.03
        color: "transparent"

        // Grid pattern
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.strokeStyle = "#333333";
                ctx.lineWidth = 1;
                ctx.globalAlpha = 0.1;

                // Draw grid
                for (var x = 0; x < width; x += 20) {
                    ctx.beginPath();
                    ctx.moveTo(x, 0);
                    ctx.lineTo(x, height);
                    ctx.stroke();
                }
                for (var y = 0; y < height; y += 20) {
                    ctx.beginPath();
                    ctx.moveTo(0, y);
                    ctx.lineTo(width, y);
                    ctx.stroke();
                }
            }
        }
    }

    // Centered and minimized chart container
    Rectangle {
        id: chartContainer
        width: parent.width * 0.8  // Increased width for better scrolling experience
        height: parent.height * 0.7  // Increased height
        anchors.centerIn: parent
        color: "#ffffff"
        radius: 10
        border.color: "#ddd"
        border.width: 1

        // Drop shadow effect
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: 2
            anchors.leftMargin: 2
            color: "#000000"
            opacity: 0.1
            radius: 10
            z: -1
        }

        ChartView {
            id: chartView
            title: "Historical Temperature Data - Interactive View"
            anchors.fill: parent
            anchors.margins: 10
            legend.visible: false
            antialiasing: true
            backgroundColor: "#fafafa"

            // Custom styling
            titleColor: "#333"
            titleFont.pixelSize: 16
            titleFont.bold: true

            LineSeries {
                id: series
                color: "#2196F3"
                width: 3

                axisX: ValueAxis {
                    id: xAxis
                    min: scrollPosition
                    max: scrollPosition + visibleDataPoints
                    titleText: "Time Index"
                    titleFont.pixelSize: 12
                    labelsFont.pixelSize: 10
                    color: "#666"
                    gridVisible: true
                    gridLineColor: "#e0e0e0"
                }

                axisY: ValueAxis {
                    id: yAxis
                    min: 0
                    max: 100
                    titleText: "Temperature (°C)"
                    titleFont.pixelSize: 12
                    labelsFont.pixelSize: 10
                    color: "#666"
                    gridVisible: true
                    gridLineColor: "#e0e0e0"
                }
            }

            // Mouse area for scrolling interaction
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                property real lastX: 0
                property bool dragging: false

                onPressed: {
                    lastX = mouse.x
                    dragging = true
                    autoScroll = false // Disable auto-scroll when user interacts
                }

                onPositionChanged: {
                    if (dragging) {
                        var deltaX = mouse.x - lastX
                        var scrollDelta = -deltaX * scrollSensitivity * 0.1

                        scrollPosition = Math.max(0, Math.min(maxScrollPosition, scrollPosition + scrollDelta))
                        updateAxisRange()

                        lastX = mouse.x
                    }
                }

                onReleased: {
                    dragging = false
                }

                // Wheel scrolling support
                onWheel: {
                    var scrollDelta = wheel.angleDelta.x * 0.01 + wheel.angleDelta.y * 0.01
                    scrollPosition = Math.max(0, Math.min(maxScrollPosition, scrollPosition - scrollDelta))
                    updateAxisRange()
                    autoScroll = false
                }
            }
        }
    }

    // Control panel for interaction (transparent background)
    Rectangle {
        id: controlPanel
        width: parent.width * 0.8
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        color: "transparent"

        Row {
            anchors.centerIn: parent
            spacing: 20

            // Auto-scroll toggle
            Rectangle {
                width: 120
                height: 35
                color: autoScroll ? "#4CAF50" : "#f44336"
                radius: 4
                border.color: "#ddd"
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    text: autoScroll ? "Auto-Scroll ON" : "Auto-Scroll OFF"
                    color: "white"
                    font.pixelSize: 12
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        autoScroll = !autoScroll
                        if (autoScroll) {
                            // Jump to latest data
                            scrollPosition = Math.max(0, maxScrollPosition)
                            updateAxisRange()
                        }
                    }
                }
            }

            // Reset view button
            Rectangle {
                width: 100
                height: 35
                color: "#2196F3"
                radius: 4
                border.color: "#ddd"
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    text: "Reset View"
                    color: "white"
                    font.pixelSize: 12
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        scrollPosition = 0
                        updateAxisRange()
                        autoScroll = false
                    }
                }
            }
        }
    }

    // Functions
    function updateAxisRange() {
        xAxis.min = scrollPosition
        xAxis.max = scrollPosition + visibleDataPoints
    }

    function updateMaxScrollPosition() {
        if (typeof temperatureModel !== 'undefined') {
            var totalPoints = temperatureModel.rowCount()
            maxScrollPosition = Math.max(0, totalPoints - visibleDataPoints)

            // Auto-scroll to latest data if enabled
            if (autoScroll) {
                scrollPosition = maxScrollPosition
                updateAxisRange()
            }
        }
    }

    // Timer for auto-scroll updates
    Timer {
        id: updateTimer
        interval: 100  // Update every 100ms
        running: true
        repeat: true
        onTriggered: {
            updateMaxScrollPosition()
        }
    }

    Component.onCompleted: {
        var mapper = Qt.createQmlObject('import QtCharts 2.15; VXYModelMapper {}', series);
        mapper.model = temperatureModel;
        mapper.xColumn = 0;
        mapper.yColumn = 1;
        mapper.series = series;

        // Initialize scroll position
        updateMaxScrollPosition()
    }
}
