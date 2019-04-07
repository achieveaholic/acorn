#include "model_provider.h"

namespace acorn {

    ModelProvider::ModelProvider() {
         initializeDBConnection();
    }

    ModelProvider* ModelProvider::_instance = nullptr;

    ModelProvider* ModelProvider::getInstace(){
        if (_instance == nullptr){
            _instance = new ModelProvider();
        }
        return _instance;
    }

    void ModelProvider::initializeDBConnection() {
        this->db = LocalDB::getInstace()->getDatabase();
    }

    /**
     * @brief loadTasks
     * @param ctxt
     */
    void ModelProvider::loadTasks(QQmlContext *ctxt){
        QList<QObject*> taskList;

        if (db.open()){
            qDebug() << "success";

            QSqlQuery query(GET_ALL_TASKS, db);
            while(query.next()){
                Task *task = new Task(query.value("id").toLongLong(),
                                      query.value("title").toString(),
                                      query.value("color").toString(),
                                      Task::Priority(query.value("prio").toInt()),
                                      query.value("done").toBool());
                taskList.append(task);
                qDebug() << (static_cast<Task::Priority>(task->prio())) << " " << (task->prio() == Task::Priority::High);
            }
        }
        else {
            qDebug() << "Could not connect to the database.";
        }

        ctxt->setContextProperty("taskList", QVariant::fromValue(taskList));
    }

    int ModelProvider::closeConnection() {
        db.close();
        return 0;
    }
}
