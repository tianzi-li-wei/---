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

            width: Math.min(parent.width - 100, (parent.height - 100) * 8 / 9)
            height: width * 9 / 8

            anchors.centerIn: parent

            radius: 8
            color: "#c98b4f"
            border.color: "#5a2f14"
            border.width: 3

            Canvas {
                id: chessBoardCanvas

                anchors.fill: parent
                anchors.margins: 36

                onWidthChanged: requestPaint()
                onHeightChanged: requestPaint()

                onPaint: {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, width, height)

                    var rows = 10
                    var cols = 9

                    var cellW = width / (cols - 1)
                    var cellH = height / (rows - 1)

                    ctx.strokeStyle = "#4a260f"
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
                    ctx.fillStyle = "#4a260f"
                    ctx.font = "bold 28px sans-serif"
                    ctx.textAlign = "center"
                    ctx.textBaseline = "middle"

                    ctx.fillText("楚 河", width * 0.28, 4.5 * cellH)
                    ctx.fillText("汉 界", width * 0.72, 4.5 * cellH)
                }
            }
        }
    }
}