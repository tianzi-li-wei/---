#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QString>

#include "BoardModel.h"
#include "../core/RuleEngine.h"
#include "../core/Constants.h"
#include "../network/NetworkManager.h"

class GameController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(int currentSide READ currentSide NOTIFY currentSideChanged)
    Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged)

    Q_PROPERTY(QString connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString playerSideText READ playerSideText NOTIFY playerSideChanged)

public:
    explicit GameController(BoardModel *boardModel,
                            QObject *parent = nullptr);

    QString statusText() const;
    int currentSide() const;
    bool gameOver() const;

    QString connectionState() const;
    QString playerSideText() const;

    void setNetworkManager(NetworkManager *networkManager);

    Q_INVOKABLE void handleQmlClick(int col, int row);
    Q_INVOKABLE void resetGame();

    Q_INVOKABLE void createRoom();
    Q_INVOKABLE void joinRoom(const QString &host);
    Q_INVOKABLE void disconnectNetwork();

public slots:
    void applyRemoteMove(int fromX,
                         int fromY,
                         int toX,
                         int toY);

signals:
    void statusTextChanged();
    void currentSideChanged();
    void gameOverChanged();

    void connectionStateChanged();
    void playerSideChanged();

private:
    void syncBoardFromEngine();
    void setStatusText(const QString &text);
    void setGameOver(bool value);
    void setConnectionState(const QString &state);
    void setPlayerSideText(const QString &sideText);
    void updateNetworkStateText();

    QString sideName(int side) const;
    int localPlayerSide() const;
    bool isNetworkMode() const;

private:
    BoardModel *m_boardModel = nullptr;
    RuleEngine m_ruleEngine;
    NetworkManager *m_networkManager = nullptr;

    int m_selectedCol = -1;
    int m_selectedRow = -1;

    QString m_statusText;
    bool m_gameOver = false;

    QString m_connectionState = "未连接";
    QString m_playerSideText = "未分配";
};

#endif // GAMECONTROLLER_H
