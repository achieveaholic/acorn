#ifndef SYSTEM_H
#define SYSTEM_H

#include <QDebug>
#include <QSysInfo>
#include <QDir>

#include "notificationclient.h"

void showSystemInfo();
void lateInit(NotificationClient *notificationClient);

#endif // SYSTEM_H
