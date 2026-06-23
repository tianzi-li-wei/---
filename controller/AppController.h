#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "BoardModel.h"
#include "GameController.h"
#include "../network/NetworkManager.h"

class AppController : public QObject
{
    Q_OBJECT

public:
    static AppController *singleton();

private:
    explicit AppController(QObject *parent = nullptr);

    AppController(const AppController &) = delete;
    AppController &operator=(const AppController &) = delete;

private:
    BoardModel m_boardModel;
    GameController m_gameController;
    NetworkManager m_networkManager;

    QQmlApplicationEngine m_engine;
};

#endif // APPCONTROLLER_H