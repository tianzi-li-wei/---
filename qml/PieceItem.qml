import QtQuick

Rectangle {
    id: piece

    property int side: 0
    property string pieceText: ""
    property bool selected: false
    property real pieceSize: 40

    visible: side !== 0

    width: pieceSize
    height: pieceSize
    radius: width / 2

    scale: selected ? 1.15 : 1.0
    z: selected ? 2 : 1

    color: selected ? "#fff176" : "#fff8e1"
    border.width: selected ? 4 : 2
    border.color: side === 1 ? "#c62828" : "#111111"

    Text {
        anchors.centerIn: parent

        text: piece.pieceText
        color: piece.side === 1 ? "#c62828" : "#111111"
        font.pixelSize: parent.width * 0.5
        font.bold: true
    }

    Behavior on scale {
        NumberAnimation {
            duration: 120
        }
    }

    Behavior on color {
        ColorAnimation {
            duration: 120
        }
    }
}