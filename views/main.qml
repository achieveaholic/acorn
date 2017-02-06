import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Acorn")
    id: wind

    property var persistentList: ListModel {
        ListElement { _id: "t1"; text: "Task 1"; color: "#eef2f0" }
        ListElement { _id: "t2"; text: "Task 2"; color: "#c6d0be" }
        ListElement { _id: "t3"; text: "Task 3"; color: "#d0bec9" }
    }

    property alias controller: controller

    function filterTasks(){
        tasks.colorModel.clear()
        for(var i = 0; i < persistentList.count; i++)
        {
            var st1 = persistentList.get(i).text
            var st2 = taskForm.filterText.text

            if(st1.toUpperCase().includes(st2.toUpperCase())){
                tasks.colorModel.append(persistentList.get(i))
            }
        }
    }

    Item {
        focus: true
        id: controller

        Keys.onPressed: {
            // On key pressed, except `Escape` and `Enter`.
            // If not visible, show filter and focus on it.
            if (!taskForm.visible && event.key != 16777216) {
                taskForm.visible = true
                taskForm.filterText.text += event.text
                taskForm.filterText.forceActiveFocus()
            }
            else {
                // Keep the focus on the text field.
                taskForm.filterText.forceActiveFocus()
            }

            // `Escape`
            if (event.key == 16777216){
                item1.visible = false
                filterText.text = ""
                filterTasks()
            }
        }
    }



    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Tasks {
            id: tasks
            TasksForm {
                id: taskForm
                visible: false
                anchors.horizontalCenter: parent.horizontalCenter

                filterButton.onClicked: {
                    taskForm.visible = false
                    controller.forceActiveFocus()
                    console.log("Set filter as: " + taskForm.filterText.text)
                }
            }

            Keys.onPressed: {
                // On key pressed, except `Escape` and `Enter`.
                // If not visible, show filter and focus on it.
                if (!taskForm.visible &&
                    event.key != 16777216 &&
                    event.key != 16777220) {
                    taskForm.visible = true
                    taskForm.filterText.text += event.text
                    taskForm.filterText.forceActiveFocus()
                }

                // `Escape`
                if (event.key == 16777216){
                    taskForm.visible = false
                    taskForm.filterText.text = ""
                    filterTasks()
                }
            }
        }

        Page {
            Label {
                text: qsTr("Projects page")
                anchors.centerIn: parent
            }
        }
    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Tasks")
        }
        TabButton {
            text: qsTr("Projects")
        }
    }
}
