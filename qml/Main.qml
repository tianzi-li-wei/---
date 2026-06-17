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

                    for (var r = 0; r < rows; r++) {
                        ctx.beginPath()
                        ctx.moveTo(0, r * cellH)
                        ctx.lineTo(width, r * cellH)
                        ctx.stroke()
                    }

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

            Repeater {
                model: boardModel

                Rectangle {
                    id: piece

                    visible: model.side !== 0

                    width: board.pieceSize
                    height: board.pieceSize
                    radius: width / 2

                    x: board.boardMargin + model.col * board.cellW - width / 2
                    y: board.boardMargin + model.row * board.cellH - height / 2

                    scale: model.selected ? 1.12 : 1.0
                    z: model.selected ? 2 : 1

                    color: model.selected ? "yellow" : "white"
                    border.width: model.selected ? 4 : 2
                    border.color: model.side === 1 ? "red" : "black"

                    Text {
                        anchors.centerIn: parent
                        text: model.text
                        color: model.side === 1 ? "red" : "black"
                        font.pixelSize: parent.width * 0.5
                        font.bold: true
                    }

                    Behavior on scale {
                        NumberAnimation {
                            duration: 120
                        }
                    }
                }
            }

            TapHandler {
                onTapped: function(eventPoint, button) {
                    var localX = eventPoint.position.x - board.boardMargin
                    var localY = eventPoint.position.y - board.boardMargin

                    if (localX < 0 || localX > board.gridWidth ||
                        localY < 0 || localY > board.gridHeight) {
                        return
                    }

                    var col = Math.round(localX / board.cellW)
                    var row = Math.round(localY / board.cellH)

                    gameController.handleQmlClick(col, row)
                }
            }
        }
    }
}