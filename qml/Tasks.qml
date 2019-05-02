import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Controls 2.5

ListView {
    id: root
    width: 640
    height: 480

    displaced: Transition {
        NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
    }

    model: DelegateModel {

        id: visualModel

        model: wind.persistentList

        delegate: MouseArea {
            id: delegateRoot

            property int visualIndex: DelegateModel.itemsIndex

            width: root.width
            height: 80
            function enableDragAndDrop() {
                if (mouseY > 25 && mouseY < 55 && mouseX >= 590 && mouseX <= 620) {
                    delegateRoot.drag.target = icon
                }
            }

            onMouseXChanged: {
                enableDragAndDrop()
            }

            onMouseYChanged: {
                enableDragAndDrop()
            }

            drag.axis: Drag.YAxis

            Rectangle {
                id: icon
                width: root.width - 8
                height: 72
                anchors {
                    horizontalCenter: parent.horizontalCenter;
                    verticalCenter: parent.verticalCenter
                }
                color: model.color
                CheckBox {
                    id: done
                    checked: taskList[model.index].done
                    anchors.verticalCenter: icon.verticalCenter

                    onCheckedChanged: {
                        if (done.checked){
                            // messageDialog.visible = true

                            taskList[model.index].done = true
                            notificationClient.notification = taskList[model.index].done
                            // TODO -> only call this when needed
                            notificationClient.notificationChanged()
                            //console.log("#88" + colorModel.get(model.index).color.substring(1,7))
                            //colorModel.get(model.index).color = "#88" + colorModel.get(model.index).color.substring(1,7)
                        }
                        else {
                            taskList[model.index].done = false
//                            notificationClient.notification = "hello qt"
//                            notificationClient.notificationChanged()

                            //console.log("#" + colorModel.get(model.index).color.substring(3,9))
                            //colorModel.get(model.index).color = "#" + colorModel.get(model.index).color.substring(3,9)
                        }
                    }
                }

                Text {
                    id: content
                    text: qsTr(model.text)
                    font.pixelSize: 20
                    // font.weight: Font.Bold
                    // font.family: "Titillium Web"
                    anchors.horizontalCenter: icon.horizontalCenter
                    anchors.verticalCenter: icon.verticalCenter
                }
                radius: 3

                Drag.active: delegateRoot.drag.active
                Drag.source: delegateRoot
                Drag.hotSpot.x: 36
                Drag.hotSpot.y: 36

                states: [
                    State {
                        when: icon.Drag.active
                        ParentChange {
                            target: icon
                            parent: root
                        }

                        AnchorChanges {
                            target: icon;
                            anchors.horizontalCenter: undefined;
                            anchors.verticalCenter: undefined
                        }
                    }
                ]

                Rectangle {
                    id: dragme
                    width: 30; height: 30; x: root.width - 55; y: 21
                    color: 'purple'
                }
            }

            DropArea {
                anchors { fill: parent; margins: 15 }

                onEntered: {
                    visualModel.items.move(drag.source.visualIndex, delegateRoot.visualIndex)
                }

                Timer {
                   id: timer
                }

                onExited: {
                    timer.interval = 300;
                    timer.repeat = false;
                    timer.triggered.connect(function () {
                        if (!delegateRoot.drag.active){
                            delegateRoot.drag.target = null;
                        }
                    })

                    timer.start();
                }
            }
        }
    }
}
