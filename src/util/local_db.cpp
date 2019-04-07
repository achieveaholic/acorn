#include "local_db.h"

namespace acorn {

    LocalDB::LocalDB() {
        initializeDatabase();
    }

    LocalDB* LocalDB::_instance = nullptr;

    LocalDB* LocalDB::getInstace(){
        if (_instance == nullptr){
            _instance = new LocalDB();
        }
        return _instance;
    }

    #ifdef Q_OS_ANDROID

    QString LocalDB::getPath() {
        __android_log_print(android_LogPriority::ANDROID_LOG_DEBUG, "Debug", "Retrieving android files path.");

        QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
        QAndroidJniObject mediaPath = mediaDir.callObjectMethod( "getAbsolutePath", "()Ljava/lang/String;" );
        QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
        QAndroidJniObject package = activity.callObjectMethod("getPackageName", "()Ljava/lang/String;");

        return mediaPath.toString() + "/Android/data/" + package.toString() + "/files/";
    }

    #elif defined(_WIN32)

    QString LocalDB::getPath() {
        return QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/";
    }

    #elif defined(__linux__)

    QString LocalDB::getPath() {
        // TODO test
        return QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/";
        // return "~/.achieveaholic/acron";
    }

    #endif

    /**
     * @brief Initialize the app database.
     */
    QString LocalDB::initializeDatabase(){
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
        if (test == nullptr) {
            qDebug() << "The database file does not exist.";

            qDebug() << "Creating the directory: " << databaseDir;
            QDir dir = QDir::root();
            if (!dir.mkpath(databaseDir)) {
                QMessageBox::critical(nullptr, tr("Error"), tr("The local database folder could not be created!"));
                exit(EXIT_FAILURE);
            }

            qDebug() << "Writing the file: " << databaseFilePath;
            writeDatabase(databaseFilePath);
        } else {
            fclose(test);
        }

        setDatabaseFilePath(databaseFilePath);
        return databaseFilePath;
    }

    /**
     * @brief writeDatabase
     * @param path
     */
    void LocalDB::writeDatabase(QString path) {
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
    bool LocalDB::fileExists(QString path) {
        QFileInfo check_file(path);
        return check_file.exists() && check_file.isFile();
    }

    QSqlDatabase LocalDB::getDatabase() {
        if (!this->db.isValid()) {
            db = QSqlDatabase::addDatabase("QSQLITE",  "db");
            db.setDatabaseName(databaseFilePath());
        }
        return db;
    }

}
