#ifndef NOTIFICATIONCLIENT_H
#define NOTIFICATIONCLIENT_H

#include <QObject>
#include <QtDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QMessageBox>

class NotificationClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notification READ notification WRITE setNotification NOTIFY notificationChanged)
public:
    explicit NotificationClient(QQmlApplicationEngine *engine);

    void setNotification(const QString &notification);
    QString notification() const;

    void loadNotification();

signals:
    void notificationChanged();

private slots:
    void updateAndroidNotification();

private:
    QString m_notification;
    QQmlApplicationEngine *m_engine;
};

#endif // NOTIFICATIONCLIENT_H
