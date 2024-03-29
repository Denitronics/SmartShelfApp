#include "appinfoitem.h"
#include "appinfomodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <blecontroller.h>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // User code

    // Declare appinfoItem in order to be accessible from QML
    AppInfoItem::DeclareQML();

    // Declare AppInfoModel object and make it accessible in QML
    AppInfoModel oAppInfoModel;
    engine.rootContext()->setContextProperty("appInfoModel", &oAppInfoModel);

    // Declare BLE Controller
    BLEController* oBLEController = new BLEController();
    engine.rootContext()->setContextProperty("bleController", oBLEController);

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
