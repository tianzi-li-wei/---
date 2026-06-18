#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "BoardModel.h"
#include "../core/RuleEngine.h"
#include "../core/Constants.h"

class GameController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(int currentSide READ currentSide NOTIFY currentSideChanged)
    Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged)

public:
    explicit GameController(BoardModel *boardModel,
                            QObject *parent = nullptr);

    QString statusText() const;
    int currentSide() const;
    bool gameOver() const;

    Q_INVOKABLE void handleQmlClick(int col, int row);
    Q_INVOKABLE void resetGame();

signals:
    void statusTextChanged();
    void currentSideChanged();
    void gameOverChanged();

private:
    void syncBoardFromEngine();
    void setStatusText(const QString &text);
    void setGameOver(bool value);
    QString sideName(int side) const;

private:
    BoardModel *m_boardModel = nullptr;
    RuleEngine m_ruleEngine;

    int m_selectedCol = -1;
    int m_selectedRow = -1;

    QString m_statusText;
    bool m_gameOver = false;
};

#endif // GAMECONTROLLER_H