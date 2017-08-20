#include "notificationclient.h"

NotificationClient::NotificationClient(QQmlApplicationEngine *engine)
{
    m_engine = engine;
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateNotification()));
    loadNotification();
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification){
        return;
    }

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

void NotificationClient::loadNotification() {
    m_engine->rootContext()->setContextProperty(QLatin1String("notificationClient"), this);
}

void NotificationClient::close(){
    m_engine->exit(0);
}

#ifdef Q_OS_ANDROID

#include <QtAndroidExtras/QAndroidJniObject>

void NotificationClient::updateNotification()
{
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
    QAndroidJniObject::callStaticMethod<void>("org/achieveaholic/acorn/NotificationClient",
                                       "notify",
                                       "(Ljava/lang/String;)V",
                                       javaNotification.object<jstring>());
}

#elif _WIN32 || __linux__

/**
 * For the desktop vesrion - initializing the tray icon.
 * @brief NotificationClient::initializeTray
 */
void NotificationClient::initializeTray()
{
    // create and initialize tray
    tray = new QSystemTrayIcon(m_engine->rootObjects().at(0));
    tray->setIcon(QIcon("d:/repo/acorn/resources/images/icon.png"));
    tray->setVisible(true);

    // create and set root menu
    QMenu* rootMenu = new QMenu("root");
    tray->setContextMenu(rootMenu);

    // create and add settings menu
    QMenu* settingsMenu = new QMenu("Settings");
    rootMenu->addMenu(settingsMenu);

    // add exit action
    QAction *exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));

    // connect exit action with the close function
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // add exit action to the root menu
    rootMenu->addAction(exitAction);
}

void NotificationClient::updateNotification()
{
    qDebug() << "Message: " << m_notification;

    // Tray message
    tray->showMessage("Hi there!", m_notification, QSystemTrayIcon::Information, 1000);

    // Message box
    QMessageBox::information(0, tr("Hello"), tr("Just testing a dialog box."));
}

#endif


