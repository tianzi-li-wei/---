import QtQuick

Rectangle {
    id: board

    property var chessBoardModel

    property int boardMargin: 36
    property real gridWidth: width - boardMargin * 2
    property real gridHeight: height - boardMargin * 2
    property real cellW: gridWidth / 8
    property real cellH: gridHeight / 9
    property real pieceSize: Math.min(cellW, cellH) * 0.72

    signal cellClicked(int col, int row)

    radius: 10
    color: "#d98c28"
    border.color: "#6b3b12"
    border.width: 3

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

            ctx.strokeStyle = "#5b2e0d"
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

            ctx.beginPath()
            ctx.moveTo(3 * cellW, 0)
            ctx.lineTo(5 * cellW, 2 * cellH)
            ctx.moveTo(5 * cellW, 0)
            ctx.lineTo(3 * cellW, 2 * cellH)
            ctx.stroke()

            ctx.beginPath()
            ctx.moveTo(3 * cellW, 7 * cellH)
            ctx.lineTo(5 * cellW, 9 * cellH)
            ctx.moveTo(5 * cellW, 7 * cellH)
            ctx.lineTo(3 * cellW, 9 * cellH)
            ctx.stroke()

            ctx.fillStyle = "#5b2e0d"
            ctx.font = "bold 28px sans-serif"
            ctx.textAlign = "center"
            ctx.textBaseline = "middle"

            ctx.fillText("楚 河", width * 0.28, 4.5 * cellH)
            ctx.fillText("汉 界", width * 0.72, 4.5 * cellH)
        }
    }

    Repeater {
        model: board.chessBoardModel

        PieceItem {
            side: model.side
            pieceText: model.text
            selected: model.selected
            pieceSize: board.pieceSize

            x: board.boardMargin + model.col * board.cellW - width / 2
            y: board.boardMargin + model.row * board.cellH - height / 2
        }
    }

     TapHandler{
        acceptedButtons: Qt.LeftButton

        onTapped: function(eventPoint, button) {
            var localX = eventPoint.position.x - board.boardMargin
            var localY = eventPoint.position.y - board.boardMargin

            var toleranceX = board.pieceSize / 2
            var toleranceY = board.pieceSize / 2

            if (localX < -toleranceX || localX > board.gridWidth + toleranceX ||
                localY < -toleranceY || localY > board.gridHeight + toleranceY) {
                return
            }

            var col = Math.round(localX / board.cellW)
            var row = Math.round(localY / board.cellH)

            col = Math.max(0, Math.min(8, col))
            row = Math.max(0, Math.min(9, row))

            board.cellClicked(col, row)
        }
    }
}