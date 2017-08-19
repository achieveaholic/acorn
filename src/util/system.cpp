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

void tray(){
    QDialog dialog;
}
