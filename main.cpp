#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "portconnection.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PortConnection *portConnection = new PortConnection;

    engine.rootContext()->setContextProperty("portConnection", portConnection);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
