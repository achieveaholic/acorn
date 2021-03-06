#include "main.h"

/**
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    app.setApplicationName("Acorn");
    app.setOrganizationName("AchieveAholic");
    app.setWindowIcon(QIcon(":/resources/images/icon.png"));

    // TODO decide which font to use here
        // App logo - TitilliumWeb?
        // ubuntu - default, ubuntu
        // windows - default
        // android - default
        // what about - Helvetica?
    QFontDatabase::addApplicationFont(":/resources/fonts/TitilliumWeb-Regular.ttf");

    QQmlApplicationEngine engine;

    acorn::NotificationClient *notificationClient = new acorn::NotificationClient(&engine);

    // --------------------------------------------------------------- //
    // TODO remove this block (from QML too)
    // QString list in QML - working example
    QStringList projectList;
    projectList.append("Project 1");
    projectList.append("Project 2");
    projectList.append("Project 3");
    projectList.append("Project 4");

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("myModel", QVariant::fromValue(projectList));
    // --------------------------------------------------------------- //
    acorn::ModelProvider *modelProvider = acorn::ModelProvider::getInstace();

    modelProvider->loadTasks(ctxt);
    // --------------------------------------------------------------- //

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    notificationClient->initializeTray();

    app.exec();

    modelProvider->closeConnection();

    return 0;
}
