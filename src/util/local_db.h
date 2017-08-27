#ifndef LOCAL_DB
#define LOCAL_DB

#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QQmlContext>

#ifdef Q_OS_ANDROID

#include <QAndroidJniObject>
#include <android/log.h>
#include <android/storage_manager.h>
#include <android/obb.h>

#endif

#include "../model/task.h"

namespace acorn {

    const QString DB_FILE_PATH = "db/local.db";

    const QString TASK_TABLE = "CREATE TABLE `Task` (\
                                        `id`	INTEGER NOT NULL,\
                                        `title`	TEXT NOT NULL,\
                                        `color`	TEXT,\
                                        `desc`	TEXT,\
                                        `prio`	INTEGER,\
                                        PRIMARY KEY(`id`)\
                                    );";

    const QString GET_ALL_TASKS = "SELECT * FROM Task";

    const QString TASK_ROWS = "INSERT INTO Task (id, title, color, desc, prio) VALUES\
                                           (1, 'Task 1', '#eef2f0', 'desc', 2),\
                                           (2, 'Task 2', '#c6d0be', 'desc', 1),\
                                           (3, 'Task 3', '#d0bec9', 'desc', 3),\
                                           (4, '" + QSysInfo::productType() + "', '#eef2f0', 'desc', 0)";

    QString getPath();

    QString initializeDatabase();

    void writeDatabase(QString);

    bool fileExists(QString);

    void setTasks(QQmlContext *ctxt);

}

#endif // LOCAL_DB
