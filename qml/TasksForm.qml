import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: filterForm
    property alias filterText: filterText
    property alias filterButton: filterButton

    RowLayout {
        anchors.top: parent.top
        anchors.topMargin: 350
        anchors.horizontalCenter: parent.horizontalCenter

        TextField {
            id: filterText
            text: ""
            font.family: "Ubuntu"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 9
            placeholderText: qsTr("Task Filter")

            Keys.onPressed: {
                // `Enter`
                if (event.key === 16777220){
                    filterForm.visible = false
                    filterTasks()
                }
                // `Escape`
                if (event.key === 16777216){
                    filterForm.visible = false
                    filterText.text = ""
                    filterTasks()
                }
            }
        }

        Button {
            id: filterButton
            width: 100
            text: qsTr("Filter")
            onPressed: {
                filterForm.visible = false
                filterTasks()
            }
        }
    }
}
