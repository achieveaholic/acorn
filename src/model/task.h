#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "../util/local_db.h"

namespace acorn {

    class Task : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(long int id READ id WRITE setId NOTIFY idChanged)
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
        //Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        //Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged)
        Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(Priority prio READ prio WRITE setPrio NOTIFY prioChanged)
        Q_PROPERTY(bool done READ done WRITE setDone NOTIFY doneChanged)

    public:
        /**
         * FIXME
         *      * Is this the right way of working with priorities? What about SQL persistance?
         *      * Thinka about a way of separating task priority from task execution order. -> paradigmn change required
         *        Create another class (Day) that will contain all the tasks due to be done today,
         *        which will index them according to an order field.
         * @brief The Priority enum
         */
        enum Priority { VeryHigh = 0, High = 1, Low = 2, VeryLow = 3};
        enum Done { NotDone = 0, Rejected = 1, Done = 2};

        explicit Task(QObject *parent = nullptr);
        explicit Task(int long id, QString text, QString color, Priority prio, bool done = false);

        void setId(long int id) { m_id = id; }
        long id() const { return m_id; }
        void setText(QString text) { m_text = text; }
        QString text() const { return m_text; }
        void setColor(QString color) { m_color = color; }
        QString color() const { return m_color; }
        void setPrio(Priority prio) { m_prio = prio; }
        Priority prio() const { return m_prio; }
        void setDone(bool done);
        long done() const { return m_done; }

    signals:
        void idChanged(long int id);
        void textChanged(QString text);
        void colorChanged(QString color);
        void prioChanged(Priority prio);
        void doneChanged(bool done);

    public slots:

    private:
        long int m_id;
        QString m_text;
        QString m_color;
        Priority m_prio;
        bool m_done;

        QSqlDatabase db;
    };

}

#endif // TASK_H
