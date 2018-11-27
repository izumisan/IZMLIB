#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mainviewmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<MainViewModel>( "viewmodels", 1, 0, "MainViewModel" );

    QQmlApplicationEngine engine;

    engine.addImportPath(QStringLiteral("qrc:///qml"));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
