#include "GameController.h"

GameController::GameController(BoardModel *boardModel,
                               QObject *parent)
    : QObject(parent),
    m_boardModel(boardModel)
{
    syncBoardFromEngine();
}

void GameController::syncBoardFromEngine()
{
    if (!m_boardModel)
    {
        qDebug() << "BoardModel is null";
        return;
    }

    m_boardModel->clearBoard();

    // 黑方
    m_boardModel->setCell(0, 0, 2, 5); // 車
    m_boardModel->setCell(1, 0, 2, 4); // 马
    m_boardModel->setCell(2, 0, 2, 3); // 象
    m_boardModel->setCell(3, 0, 2, 2); // 士
    m_boardModel->setCell(4, 0, 2, 1); // 将
    m_boardModel->setCell(5, 0, 2, 2); // 士
    m_boardModel->setCell(6, 0, 2, 3); // 象
    m_boardModel->setCell(7, 0, 2, 4); // 马
    m_boardModel->setCell(8, 0, 2, 5); // 車

    m_boardModel->setCell(1, 2, 2, 6); // 炮
    m_boardModel->setCell(7, 2, 2, 6); // 炮

    m_boardModel->setCell(0, 3, 2, 7); // 卒
    m_boardModel->setCell(2, 3, 2, 7); // 卒
    m_boardModel->setCell(4, 3, 2, 7); // 卒
    m_boardModel->setCell(6, 3, 2, 7); // 卒
    m_boardModel->setCell(8, 3, 2, 7); // 卒

    // 红方
    m_boardModel->setCell(0, 9, 1, 5); // 車
    m_boardModel->setCell(1, 9, 1, 4); // 马
    m_boardModel->setCell(2, 9, 1, 3); // 相
    m_boardModel->setCell(3, 9, 1, 2); // 仕
    m_boardModel->setCell(4, 9, 1, 1); // 帅
    m_boardModel->setCell(5, 9, 1, 2); // 仕
    m_boardModel->setCell(6, 9, 1, 3); // 相
    m_boardModel->setCell(7, 9, 1, 4); // 马
    m_boardModel->setCell(8, 9, 1, 5); // 車

    m_boardModel->setCell(1, 7, 1, 6); // 炮
    m_boardModel->setCell(7, 7, 1, 6); // 炮

    m_boardModel->setCell(0, 6, 1, 7); // 兵
    m_boardModel->setCell(2, 6, 1, 7); // 兵
    m_boardModel->setCell(4, 6, 1, 7); // 兵
    m_boardModel->setCell(6, 6, 1, 7); // 兵
    m_boardModel->setCell(8, 6, 1, 7); // 兵
}

void GameController::handleQmlClick(int x, int y)
{
    qDebug() << "QML clicked:" << x << y;

    if (!m_boardModel)
    {
        qDebug() << "BoardModel is null";
        return;
    }

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
        sideText = "空位置";
    }

    qDebug() << "Clicked piece side:" << sideText;

    if (piece.side != 0)
    {
        m_boardModel->setSelected(x, y);
    }
    else
    {
        m_boardModel->clearSelected();
    }
}