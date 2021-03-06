#include "system.h"

namespace acorn {

    /**
     * @brief showSystemInfo
     */
    void showSystemInfo() {
        qDebug() << "Home Directory: " << QDir::homePath();
        qDebug() << "Current Path: " << QDir::currentPath();

        qDebug() << "Operating System: " << QSysInfo::prettyProductName();
        qDebug() << "Operating System Version: " << QSysInfo::productType();
    }

}
