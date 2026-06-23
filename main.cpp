#include <QGuiApplication>

#include "controller/AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AppController::singleton();

    return QGuiApplication::exec();
}