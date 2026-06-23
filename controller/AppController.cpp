#include "AppController.h"

#include <QCoreApplication>
#include <QQmlContext>

AppController *AppController::singleton()
{
    static AppController *instance = new AppController;
    return instance;
}

AppController::AppController(QObject *parent)
    : QObject(parent),
    m_boardModel(this),
    m_gameController(&m_boardModel, this),
    m_networkManager(this)
{
    m_gameController.setNetworkManager(&m_networkManager);

    m_engine.rootContext()->setContextProperty("boardModel", &m_boardModel);
    m_engine.rootContext()->setContextProperty("gameController", &m_gameController);
    m_engine.rootContext()->setContextProperty("networkManager", &m_networkManager);

    QObject::connect(
        &m_engine,
        &QQmlApplicationEngine::objectCreationFailed,
        QCoreApplication::instance(),
        []() {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    m_engine.loadFromModule("Xiangqi", "Main");
}