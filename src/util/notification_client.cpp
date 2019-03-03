/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "notification_client.h"

namespace acorn {

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

    void NotificationClient::updateNotification()
    {
        QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
        QAndroidJniObject::callStaticMethod<void>("org/achieveaholic/acorn/NotificationClient",
                                           "notify",
                                           "(Ljava/lang/String;)V",
                                           javaNotification.object<jstring>());
    }

    #elif defined(_WIN32) || defined(__linux__)

    void NotificationClient::updateNotification()
    {
        qDebug() << "Message: " << m_notification;

        // Tray message
        tray->showMessage("Hi there!", m_notification, QSystemTrayIcon::Information, 1000);

        // Message box
        QMessageBox::information(nullptr, tr("Hello"), tr("Just testing a dialog box."));
    }

    #endif


    /**
     * For the desktop vesrion - initializing the tray icon.
     * @brief NotificationClient::initializeTray
     */
    void NotificationClient::initializeTray()
    {
        #ifdef Q_OS_ANDROID

        // do nothing

        #elif defined(_WIN32) || defined(__linux__)

        // create and initialize tray
        tray = new QSystemTrayIcon(m_engine->rootObjects().at(0));
        tray->setIcon(QIcon(":/resources/images/icon.png"));
        tray->setVisible(true);

        // create and set root menu
        QMenu* rootMenu = new QMenu("root");
        tray->setContextMenu(rootMenu);

        // create and add settings menu
        QMenu* settingsMenu = new QMenu("Settings");
        rootMenu->addMenu(settingsMenu);

        // create and add exit action
        QAction *exitAction = new QAction(tr("E&xit"), this);
        exitAction->setShortcuts(QKeySequence::Quit);
        exitAction->setStatusTip(tr("Exit the application"));

        // connect exit action with the close function
        connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

        // add exit action to the root menu
        rootMenu->addAction(exitAction);

        #endif
    }

}
