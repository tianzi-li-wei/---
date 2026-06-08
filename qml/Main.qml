import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window

    width: 900
    height: 760
    minimumWidth: 760
    minimumHeight: 680

    visible: true
    title: "Xiangqi - 中国象棋"

    color: "#1f1f1f"

    header: ToolBar {
        height: 56

        Label {
            anchors.centerIn: parent
            text: "Xiangqi 中国象棋"
            font.pixelSize: 22
            font.bold: true
            color: "white"
        }
    }

    Rectangle {
        id: background

        anchors.fill: parent
        anchors.margins: 20

        radius: 16
        color: "#2b2b2b"
        border.color: "#555555"
        border.width: 1

        Rectangle {
            id: board

            width: Math.min(parent.width - 80, parent.height - 80)
            height: width

            anchors.centerIn: parent

            radius: 8
            color: "#c98b4f"
            border.color: "#5a2f14"
            border.width: 3

            Column {
                anchors.centerIn: parent
                spacing: 12

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "棋盘区域"
                    font.pixelSize: 32
                    font.bold: true
                    color: "#4a260f"
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 16
                    color: "#4a260f"
                }
            }
        }
    }
}