#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include "controller/BoardModel.h"
#include "controller/GameController.h"
#include "network/NetworkManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    BoardModel boardModel;
    GameController gameController(&boardModel);
    NetworkManager networkManager;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("boardModel", &boardModel);
    engine.rootContext()->setContextProperty("gameController", &gameController);
    engine.rootContext()->setContextProperty("networkManager", &networkManager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.loadFromModule("Xiangqi", "Main");

    return app.exec();
}