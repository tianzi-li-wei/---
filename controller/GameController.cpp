#include "GameController.h"

// 就是你原来写的这些实现代码，直接放这里
// 同步棋盘数据从引擎到UI的方法
void GameController::syncBoardFromEngine()
{
    if (!m_boardModel)
        return;
    // 你的同步逻辑...
}

// QML点击处理函数
void GameController::handleQmlClick(int x, int y)
{
    // 提示已经给你写好了，按你项目改方法名即可
    CellData piece = m_boardModel->getCellAt(x, y);
    QString sideText;
    if (piece.side == 1)
    {
        sideText = "红方";
    }
    else if (piece.side == 2)
    {
        sideText = "黑方";
    }
    else
    {
        sideText = "未知";
    }
    // 你自己后续的逻辑加在这里就行
}