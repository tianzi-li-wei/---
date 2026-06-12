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

    color: "black"


    Rectangle {
        id: background

        anchors.fill: parent
        anchors.margins: 20

        radius: 16
        color: "gray"
        border.color: "white"
        border.width: 1

        Rectangle {
            id: board

            width: Math.min(parent.width - 100, (parent.height - 100) * 8 / 9)
            height: width * 9 / 8

            anchors.centerIn: parent

            radius: 8
            color: "orange"
            border.color: "brown"
            border.width: 3

            property int boardMargin: 36
            property real gridWidth: width - boardMargin * 2
            property real gridHeight: height - boardMargin * 2
            property real cellW: gridWidth / 8
            property real cellH: gridHeight / 9
            property real pieceSize: Math.min(cellW, cellH) * 0.72

            Canvas {
                id: chessBoardCanvas

                anchors.fill: parent
                anchors.margins: board.boardMargin

                onWidthChanged: requestPaint()
                onHeightChanged: requestPaint()

                onPaint: {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, width, height)

                    var rows = 10
                    var cols = 9

                    var cellW = width / (cols - 1)
                    var cellH = height / (rows - 1)

                    ctx.strokeStyle = "brown"
                    ctx.lineWidth = 2

                    // 画横线：10 行
                    for (var r = 0; r < rows; r++) {
                        ctx.beginPath()
                        ctx.moveTo(0, r * cellH)
                        ctx.lineTo(width, r * cellH)
                        ctx.stroke()
                    }

                    // 画竖线：9 列，中间留出楚河汉界
                    for (var c = 0; c < cols; c++) {
                        var x = c * cellW

                        ctx.beginPath()

                        if (c === 0 || c === cols - 1) {
                            ctx.moveTo(x, 0)
                            ctx.lineTo(x, height)
                        } else {
                            ctx.moveTo(x, 0)
                            ctx.lineTo(x, 4 * cellH)

                            ctx.moveTo(x, 5 * cellH)
                            ctx.lineTo(x, height)
                        }

                        ctx.stroke()
                    }

                    // 上方九宫格
                    ctx.beginPath()
                    ctx.moveTo(3 * cellW, 0)
                    ctx.lineTo(5 * cellW, 2 * cellH)
                    ctx.moveTo(5 * cellW, 0)
                    ctx.lineTo(3 * cellW, 2 * cellH)
                    ctx.stroke()

                    // 下方九宫格
                    ctx.beginPath()
                    ctx.moveTo(3 * cellW, 7 * cellH)
                    ctx.lineTo(5 * cellW, 9 * cellH)
                    ctx.moveTo(5 * cellW, 7 * cellH)
                    ctx.lineTo(3 * cellW, 9 * cellH)
                    ctx.stroke()

                    // 楚河汉界
                    ctx.fillStyle = "brown"
                    ctx.font = "bold 28px sans-serif"
                    ctx.textAlign = "center"
                    ctx.textBaseline = "middle"

                    ctx.fillText("楚 河", width * 0.28, 4.5 * cellH)
                    ctx.fillText("汉 界", width * 0.72, 4.5 * cellH)
                }
            }

            ListModel {
                id: pieceModel

                // 黑方
                ListElement { col: 0; row: 0; side: "black"; text: "车" }
                ListElement { col: 1; row: 0; side: "black"; text: "马" }
                ListElement { col: 2; row: 0; side: "black"; text: "象" }
                ListElement { col: 3; row: 0; side: "black"; text: "士" }
                ListElement { col: 4; row: 0; side: "black"; text: "将" }
                ListElement { col: 5; row: 0; side: "black"; text: "士" }
                ListElement { col: 6; row: 0; side: "black"; text: "象" }
                ListElement { col: 7; row: 0; side: "black"; text: "马" }
                ListElement { col: 8; row: 0; side: "black"; text: "车" }

                ListElement { col: 1; row: 2; side: "black"; text: "炮" }
                ListElement { col: 7; row: 2; side: "black"; text: "炮" }

                ListElement { col: 0; row: 3; side: "black"; text: "卒" }
                ListElement { col: 2; row: 3; side: "black"; text: "卒" }
                ListElement { col: 4; row: 3; side: "black"; text: "卒" }
                ListElement { col: 6; row: 3; side: "black"; text: "卒" }
                ListElement { col: 8; row: 3; side: "black"; text: "卒" }

                // 红方
                ListElement { col: 0; row: 9; side: "red"; text: "车" }
                ListElement { col: 1; row: 9; side: "red"; text: "马" }
                ListElement { col: 2; row: 9; side: "red"; text: "相" }
                ListElement { col: 3; row: 9; side: "red"; text: "仕" }
                ListElement { col: 4; row: 9; side: "red"; text: "帅" }
                ListElement { col: 5; row: 9; side: "red"; text: "仕" }
                ListElement { col: 6; row: 9; side: "red"; text: "相" }
                ListElement { col: 7; row: 9; side: "red"; text: "马" }
                ListElement { col: 8; row: 9; side: "red"; text: "车" }

                ListElement { col: 1; row: 7; side: "red"; text: "炮" }
                ListElement { col: 7; row: 7; side: "red"; text: "炮" }

                ListElement { col: 0; row: 6; side: "red"; text: "兵" }
                ListElement { col: 2; row: 6; side: "red"; text: "兵" }
                ListElement { col: 4; row: 6; side: "red"; text: "兵" }
                ListElement { col: 6; row: 6; side: "red"; text: "兵" }
                ListElement { col: 8; row: 6; side: "red"; text: "兵" }
            }

            Repeater {
                model: pieceModel

                Rectangle {
                    width: board.pieceSize
                    height: board.pieceSize
                    radius: width / 2

                    x: board.boardMargin + model.col * board.cellW - width / 2
                    y: board.boardMargin + model.row * board.cellH - height / 2

                    color: "white"
                    border.width: 2
                    border.color: model.side === "red" ? "red" : "black"

                    Text {
                        anchors.centerIn: parent
                        text: model.text
                        color: model.side === "red" ? "red" : "black"
                        font.pixelSize: parent.width * 0.5
                        font.bold: true
                    }
                }
            }
        }
    }
}