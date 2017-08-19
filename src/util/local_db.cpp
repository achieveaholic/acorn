#include "local_db.h"

#ifdef Q_OS_ANDROID

#include <QAndroidJniObject>
#include <android/log.h>
#include <android/storage_manager.h>
#include <android/obb.h>


QString getPath() {
    __android_log_print(android_LogPriority::ANDROID_LOG_DEBUG, "Debug", "Retrieving android files path.");

    QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
    QAndroidJniObject mediaPath = mediaDir.callObjectMethod( "getAbsolutePath", "()Ljava/lang/String;" );
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject package = activity.callObjectMethod("getPackageName", "()Ljava/lang/String;");

    return mediaPath.toString() + "/Android/data/" + package.toString() + "/files/";
}

#elif _WIN32

QString getPath() {
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/";
}

#elif __linux__

QString getPath() {
    // TODO test
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/";
    // return "~/.achieveaholic/acron";
}

#endif


/**
 * @brief Initialize the app database.
 */
QString initializeDatabase(){
    QString databaseDir = getPath() + "db";
    QString databaseFilePath = getPath() + DB_FILE_PATH;

    QDir dir(databaseDir);
    if (not dir.exists()){
        dir.mkpath(databaseDir);
    }
    else {
        qDebug() << databaseDir << " already exists!";
    }

    FILE* test =  fopen(databaseFilePath.toLocal8Bit(), "r");
    if (test == NULL) {
        qDebug() << "The database file does not exist.";

        qDebug() << "Creating the directory: " << databaseDir;
        QDir dir = QDir::root();
        dir.mkpath(databaseDir);

        // FIXME if the directory creation fails, warn user about required permission -> Storage

        qDebug() << "Writing the file: " << databaseFilePath;
        writeDatabase(databaseFilePath);
    }
    fclose(test);

    return databaseFilePath;
}

/**
 * @brief writeDatabase
 * @param path
 */
void writeDatabase(QString path) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(db.open()){
        QSqlQuery create(TASK_TABLE, db);
        QSqlQuery insert(TASK_ROWS, db);
        db.commit();
        db.close();

        qDebug() << "Database created.";
    }
    else {
        qDebug() << "Could not create database.";
    }
}

/**
 * @brief Check if the path refers to an existing file.
 * @param path
 */
bool fileExists(QString path) {
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile();
}

/**
 * @brief setTasks
 * @param ctxt
 */
void setTasks(QQmlContext *ctxt){
    QList<QObject*> taskList;
    QString databaseFilePath = initializeDatabase();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseFilePath);
    if (db.open()){
        qDebug() << "success";

        QSqlQuery query(GET_ALL_TASKS, db);
        while(query.next()){
            /*
            qDebug() << "-> " << query.value("id").toLongLong() << " "
                              << query.value("title").toString() << " "
                              << query.value(3).toInt() << " "
                              << query.value(2).toString();
                              */

            Task *task = new Task(query.value("id").toLongLong(),
                                  query.value("title").toString(),
                                  query.value("color").toString(),
                                  Task::Priority(query.value("prio").toInt()),
                                  false);
            taskList.append(task);
            qDebug() << (static_cast<Task::Priority>(task->prio())) << " " << (task->prio() == Task::Priority::High);
        }

        db.close();
    }
    else {
        qDebug() << "Could not connect to the database.";
    }

    ctxt->setContextProperty("taskList", QVariant::fromValue(taskList));
}


// TODO create a class for hadling the database(s)


