#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "BoardModel.h"

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(BoardModel *boardModel,
                            QObject *parent = nullptr);

    void syncBoardFromEngine();

    Q_INVOKABLE void handleQmlClick(int x, int y);

private:
    BoardModel *m_boardModel = nullptr;
};

#endif // GAMECONTROLLER_H