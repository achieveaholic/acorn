#include "task.h"

Task::Task(int long id, QString text, QString color, Priority prio, bool done){
    setId(id);
    setText(text);
    setColor(color);
    setPrio(prio);
    setDone(done);
}

/*
void Task::colorChanged(QString color){
    qDebug("test");
}

void Task::prioChanged(Priority prio){
    qDebug("test");
}
*/
