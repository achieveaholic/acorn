#include "notificationclient.h"

NotificationClient::NotificationClient(QQmlApplicationEngine *engine)
{
    m_engine = engine;
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification)
        return;

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

#ifdef Q_OS_ANDROID

#include <QtAndroidExtras/QAndroidJniObject>

void NotificationClient::updateAndroidNotification()
{
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
    QAndroidJniObject::callStaticMethod<void>("org/achieveaholic/acorn/NotificationClient",
                                       "notify",
                                       "(Ljava/lang/String;)V",
                                       javaNotification.object<jstring>());
}

#elif _WIN32 || __linux__

void NotificationClient::updateAndroidNotification()
{
    // FIXME add desktop notification
    qDebug() << "Message: " << m_notification;
//    QSystemTrayIcon *tray = new QSystemTrayIcon(m_engine->rootObjects().at(0));
//    tray->setIcon(QIcon("d:/repo/acorn/resources/images/tray.png"));
//    //tray->setVisible(true);
//    QMenu* menu = new QMenu("tesst");

//    QAction *exitAct = new QAction(tr("E&xit"), this);
//    exitAct->setShortcuts(QKeySequence::Quit);
//    exitAct->setStatusTip(tr("Exit the application"));

//    menu->addAction(exitAct);
//    tray->setContextMenu(menu);
//    //tray->setToolTip("unko!");
//    //tray->show();
//    tray->showMessage("Hi there!", m_notification, QSystemTrayIcon::Information, 1000);

//    QMessageBox::information(0, tr("Systray"),
//                                 tr("Sorry, I already gave what help I could.\n"
//                                    "Maybe you should try asking a human?"));
}

#endif


