#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{

}

Task::Task(int long id, QString text, QString color, Priority prio, bool done){
    setId(id);
    setText(text);
    setColor(color);
    setPrio(prio);
    setDone(done);
}

// ---------------------------------------- //
// Pehaps handle these signals in the solts //
// of a Database connection class.          //
// ---------------------------------------- //

/*
void Task::colorChanged(QString color){
    qDebug("test");
}

void Task::prioChanged(Priority prio){
    qDebug("test");
}
*/
