#ifndef MODEL_PROVIDER_H
#define MODEL_PROVIDER_H

#include <QObject>

#include "../model/task.h"
#include "../util/local_db.h"

namespace acorn {

    class ModelProvider : public QObject
    {
        Q_OBJECT

        const QString GET_ALL_TASKS = "SELECT * FROM Task";

    public:

            static ModelProvider* getInstace();
            void loadTasks(QQmlContext *ctxt);
            int closeConnection();

    private:

            QSqlDatabase db;
            void initializeDBConnection();
            static ModelProvider* _instance;
            explicit ModelProvider();
    };
}

#endif // MODEL_PROVIDER_H
