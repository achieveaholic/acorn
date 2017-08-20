#include "system.h"

/**
 * @brief showSystemInfo
 */
void showSystemInfo() {
    qDebug() << "Home Directory: " << QDir::homePath();
    qDebug() << "Current Path: " << QDir::currentPath();

    qDebug() << "Operating System: " << QSysInfo::prettyProductName();
    qDebug() << "Operating System Version: " << QSysInfo::productType();
}

/**
 * A placeholder function for delayed initializations.
 * @brief lateInit
 * @param notificationClient
 */
void lateInit(NotificationClient &notificationClient) {

#ifdef Q_OS_ANDROID

#elif defined(_WIN32) || defined(__linux__)

    notificationClient.initializeTray();

#endif
}
