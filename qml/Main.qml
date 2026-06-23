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

    color: "#202020"

    property bool gameOverDialogClosed: false

    function currentSideText(side) {
        if (side === 1) {
            return "红方回合"
        }

        if (side === 2) {
            return "黑方回合"
        }

        return "等待开始"
    }

    function currentSideColor(side) {
        if (side === 1) {
            return "#ff8a80"
        }

        if (side === 2) {
            return "#e0e0e0"
        }

        return "#ffcc80"
    }

    Connections {
        target: gameController

        function onGameOverChanged() {
            if (gameController.gameOver) {
                window.gameOverDialogClosed = false
            }
        }
    }

    Rectangle {
        id: background

        anchors.fill: parent
        anchors.margins: 20

        radius: 16
        color: "#4a4a4a"
        border.color: "white"
        border.width: 1

        // 顶部状态栏
        Rectangle {
            id: topPanel

            height: 58
            radius: 12
            color: "#2f2f2f"

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 18

            Text {
                id: titleText

                anchors.left: parent.left
                anchors.leftMargin: 24
                anchors.verticalCenter: parent.verticalCenter

                text: "中国象棋"
                color: "white"
                font.pixelSize: 22
                font.bold: true
            }

            Text {
                id: turnText

                anchors.centerIn: parent

                text: window.currentSideText(gameController.currentSide)
                color: window.currentSideColor(gameController.currentSide)
                font.pixelSize: 24
                font.bold: true
            }

            Text {
                id: versionText

                anchors.right: parent.right
                anchors.rightMargin: 24
                anchors.verticalCenter: parent.verticalCenter

                text: "本地对弈版"
                color: "#dddddd"
                font.pixelSize: 16
            }
        }

        // 棋盘组件
        BoardView {
            id: boardView

            width: Math.min(parent.width - 120, (parent.height - 180) * 8 / 9)
            height: width * 9 / 8

            anchors.centerIn: parent

            chessBoardModel: boardModel

            onCellClicked: function(col, row) {
                gameController.handleQmlClick(col, row)
            }
        }

        // 底部提示栏
        Rectangle {
            id: bottomPanel

            height: 58
            radius: 12
            color: "#2f2f2f"

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 18

            Text {
                id: statusText

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 24
                anchors.right: restartButton.left
                anchors.rightMargin: 20

                text: gameController.statusText
                color: "white"
                font.pixelSize: 20
                elide: Text.ElideRight
            }

            Button {
                id: restartButton

                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20

                text: "重新开始"

                onClicked: {
                    window.gameOverDialogClosed = false
                    gameController.resetGame()
                }
            }
        }
    }

    // 游戏结束弹窗
    Dialog {
        id: gameOverDialog

        modal: true
        title: "游戏结束"

        visible: gameController.gameOver && !window.gameOverDialogClosed

        anchors.centerIn: parent

        standardButtons: Dialog.Ok

        onAccepted: {
            window.gameOverDialogClosed = true
        }

        contentItem: Text {
            width: 260
            padding: 24

            text: gameController.statusText
            color: "black"
            font.pixelSize: 24
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }
    }
}