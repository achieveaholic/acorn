#include "task.h"

namespace acorn {

    Task::Task(int long id, QString text, QString color, Priority prio, bool done){
        this->db = LocalDB::getInstace()->getDatabase();

        this->m_id = id;
        this->m_text = text;
        this->m_color = color;
        this->m_prio = prio;
        this->m_done = done;
    }

    /*
    void Task::colorChanged(QString color){
        qDebug("test");
    }

    void Task::prioChanged(Priority prio){
        qDebug("test");
    }
    */

    // TODO refactor, to avoid duplicate code (for other set methods)
    void Task::setDone(bool done){
        m_done = done;

        qDebug() << this->text() << " is done: " << done;

        if(db.open()){
            // FIXME sanitize the input here
            // TODO use a constant here
            QString q = "UPDATE task SET done = " + QString::number(done ? 1 : 0) + " WHERE id == "  + QString::number(this->id()) + ";";
            qDebug() << q;
            QSqlQuery insert(q, db);
            db.commit();

            qDebug() << "Task done state was updated.";
        }
        else {
            qDebug() << "Could not update date state.";
        }
    }

}
