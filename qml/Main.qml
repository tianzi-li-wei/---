import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window

    width: 1080
    height: 760
    minimumWidth: 960
    minimumHeight: 680

    visible: true
    title: "Xiangqi - 中国象棋"

    color: "#202020"

    property bool gameOverDialogClosed: false
    property string localNetworkMessage: "联网功能待接入"

    function currentSideText(side) {
        if (side === 1) {
            return "红方回合"
        }

        if (side === 2) {
            return "黑方回合"
        }

        return "等待开始"
    }

    function connectionStateText() {
        if (networkManager.statusText !== undefined &&
            networkManager.statusText !== null &&
            networkManager.statusText !== "") {
            return networkManager.statusText
        }

        return "未连接"
    }

    function playerSideText() {
        if (networkManager.isHost) {
            return "红方"
        }

        if (networkManager.connected) {
            return "黑方"
        }

        return "未分配"
    }

    function createRoomClicked() {
        networkManager.hostRoom(45454)
        window.localNetworkMessage = "正在创建房间..."
    }

    function joinRoomClicked(host) {
        if (host.length === 0) {
            window.localNetworkMessage = "请输入对方 IP 地址"
            return
        }

        networkManager.joinRoom(host, 45454)
        window.localNetworkMessage = "正在连接：" + host
    }

    function disconnectClicked() {
        networkManager.disconnectFromRoom()
        window.localNetworkMessage = "已断开连接"
    }
    Connections {
        target: networkManager

        function onStatusTextChanged() {
            window.localNetworkMessage = networkManager.statusText
        }

        function onConnectedChanged() {
            if (networkManager.connected) {
                window.localNetworkMessage = "连接成功"
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

                   text: "局域网联机版"
                   color: "#dddddd"
                   font.pixelSize: 16
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
           // 右侧联网面板
                  Rectangle {
                      id: networkPanel

                      width: 250
                      radius: 12
                      color: "#303030"
                      border.color: "#777777"
                      border.width: 1

                      anchors.top: topPanel.bottom
                      anchors.topMargin: 18
                      anchors.right: parent.right
                      anchors.rightMargin: 18
                      anchors.bottom: bottomPanel.top
                      anchors.bottomMargin: 18

                      Column {
                          id: networkColumn

                          anchors.fill: parent
                          anchors.margins: 18

                          spacing: 14

                          Text {
                              text: "联机控制"
                              color: "white"
                              font.pixelSize: 22
                              font.bold: true
                          }

                          Rectangle {
                              width: parent.width
                              height: 1
                              color: "#666666"
                          }

                          Text {
                              text: "连接状态"
                              color: "#bbbbbb"
                              font.pixelSize: 14
                          }

                          Text {
                              width: parent.width
                              text: window.connectionStateText()
                              color: "#ffcc80"
                              font.pixelSize: 18
                              font.bold: true
                              wrapMode: Text.WordWrap
                          }

                          Text {
                              text: "玩家身份"
                              color: "#bbbbbb"
                              font.pixelSize: 14
                          }

                          Text {
                              width: parent.width
                              text: window.playerSideText()
                              color: "#90caf9"
                              font.pixelSize: 18
                              font.bold: true
                              wrapMode: Text.WordWrap
                          }

                          Rectangle {
                              width: parent.width
                              height: 1
                              color: "#666666"
                          }

                          Button {
                              width: parent.width
                              text: "创建房间"

                              onClicked: {
                                  window.createRoomClicked()
                              }
                          }

                          TextField {
                              id: ipInput

                              width: parent.width
                              placeholderText: "输入对方 IP"
                              text: ""
                              selectByMouse: true
                          }

                          Button {
                              width: parent.width
                              text: "加入房间"

                              onClicked: {
                                  window.joinRoomClicked(ipInput.text.trim())
                              }
                          }

                          Button {
                              width: parent.width
                              text: "断开连接"

                              onClicked: {
                                  window.disconnectClicked()
                              }
                          }

                          Rectangle {
                              width: parent.width
                              height: 1
                              color: "#666666"
                          }

                          Text {
                              text: "前端提示"
                              color: "#bbbbbb"
                              font.pixelSize: 14
                          }

                          Text {
                              width: parent.width
                              text: window.localNetworkMessage
                              color: "#dddddd"
                              font.pixelSize: 15
                              wrapMode: Text.WordWrap
                          }
                      }
                  }
                  // 棋盘组件
                        BoardView {
                            id: boardView

                            width: Math.min(
                                       parent.width - networkPanel.width - 130,
                                       (parent.height - 180) * 8 / 9
                                   )

                            height: width * 9 / 8

                            anchors.left: parent.left
                            anchors.leftMargin: 48
                            anchors.verticalCenter: parent.verticalCenter

                            chessBoardModel: boardModel

                            onCellClicked: function(col, row) {
                                gameController.handleQmlClick(col, row)
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
                }