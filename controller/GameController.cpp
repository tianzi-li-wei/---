#include "GameController.h"

GameController::GameController(BoardModel *boardModel,
                               QObject *parent)
    : QObject(parent),
    m_boardModel(boardModel)
{
    syncBoardFromEngine();
    setStatusText("红方先行");
}

QString GameController::statusText() const
{
    return m_statusText;
}

int GameController::currentSide() const
{
    return m_ruleEngine.currentPlayer();
}

bool GameController::gameOver() const
{
    return m_gameOver;
}

QString GameController::connectionState() const
{
    return m_connectionState;
}

QString GameController::playerSideText() const
{
    return m_playerSideText;
}

void GameController::resetGame()
{
    m_ruleEngine.initializeBoard();

    m_selectedCol = -1;
    m_selectedRow = -1;

    setGameOver(false);

    if (m_boardModel)
    {
        m_boardModel->clearSelected();
    }

    syncBoardFromEngine();

    emit currentSideChanged();

    setStatusText("新游戏开始，红方先行");
}

void GameController::createRoom()
{
    setConnectionState("等待连接");
    setPlayerSideText("红方");

    setStatusText("已创建房间，等待对方连接");
}

void GameController::joinRoom(const QString &host)
{
    QString trimmedHost = host.trimmed();

    if (trimmedHost.isEmpty())
    {
        setStatusText("请输入对方 IP 地址");
        return;
    }

    setConnectionState("正在连接");
    setPlayerSideText("黑方");

    setStatusText(QString("正在连接：%1").arg(trimmedHost));
}

void GameController::disconnectNetwork()
{
    setConnectionState("未连接");
    setPlayerSideText("未分配");

    setStatusText("已断开连接");
}

void GameController::handleQmlClick(int col, int row)
{
    if (!m_boardModel)
    {
        setStatusText("棋盘模型未初始化");
        return;
    }

    if (m_gameOver)
    {
        setStatusText("游戏已经结束，请点击重新开始");
        return;
    }

    CellData clickedCell = m_boardModel->getCellAt(col, row);
    int current = m_ruleEngine.currentPlayer();

    if (m_selectedCol < 0 || m_selectedRow < 0)
    {
        if (clickedCell.side == 0)
        {
            setStatusText(QString("%1走棋，请选择自己的棋子")
                              .arg(sideName(current)));
            return;
        }

        if (clickedCell.side != current)
        {
            setStatusText(QString("现在是%1回合，不能选择%2棋子")
                              .arg(sideName(current), sideName(clickedCell.side)));
            return;
        }

        m_selectedCol = col;
        m_selectedRow = row;

        m_boardModel->setSelected(col, row);

        setStatusText(QString("已选择%1棋子：%2")
                          .arg(sideName(clickedCell.side), clickedCell.text));

        return;
    }
    if (clickedCell.side == current)
    {
        m_selectedCol = col;
        m_selectedRow = row;

        m_boardModel->setSelected(col, row);

        setStatusText(QString("已重新选择%1棋子：%2")
                          .arg(sideName(clickedCell.side), clickedCell.text));

        return;
    }

    MoveResult result = m_ruleEngine.movePiece(m_selectedCol,
                                               m_selectedRow,
                                               col,
                                               row);

    if (!result.success)
    {
        setStatusText("非法走法，请重新选择目标位置");
        return;
    }

    m_selectedCol = -1;
    m_selectedRow = -1;

    m_boardModel->clearSelected();
    syncBoardFromEngine();

    emit currentSideChanged();

    if (result.gameOver)
    {
        setGameOver(true);

        setStatusText(QString("游戏结束，%1获胜")
                          .arg(sideName(result.winner)));
        return;
    }

    setStatusText(QString("走棋成功，轮到%1")
                      .arg(sideName(m_ruleEngine.currentPlayer())));
}

void GameController::syncBoardFromEngine()
{
    if (!m_boardModel)
    {
        return;
    }

    m_boardModel->clearBoard();

    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            Piece piece = m_ruleEngine.queryPiece(col, row);

            m_boardModel->setCell(col,
                                  row,
                                  piece.side,
                                  piece.type);
        }
    }
}

void GameController::setStatusText(const QString &text)
{
    if (m_statusText == text)
    {
        return;
    }

    m_statusText = text;
    emit statusTextChanged();
}

void GameController::setGameOver(bool value)
{
    if (m_gameOver == value)
    {
        return;
    }

    m_gameOver = value;
    emit gameOverChanged();
}

void GameController::setConnectionState(const QString &state)
{
    if (m_connectionState == state)
    {
        return;
    }

    m_connectionState = state;
    emit connectionStateChanged();
}

void GameController::setPlayerSideText(const QString &sideText)
{
    if (m_playerSideText == sideText)
    {
        return;
    }

    m_playerSideText = sideText;
    emit playerSideChanged();
}

QString GameController::sideName(int side) const
{
    if (side == Xiangqi::SIDE_RED)
    {
        return "红方";
    }

    if (side == Xiangqi::SIDE_BLACK)
    {
        return "黑方";
    }

    return "无";
}