import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13

Item {
    id: element
    height:800
    width:100

    property var model
    signal changeAffichage(var nb)
    property int indiceAffiche:0

    Column {
        id: column
        anchors.fill: parent

        Repeater
        {
            id:repeater
            model:element.model
            anchors.fill: parent

            ColumnLayout {
                id: rowLayout
                width: 100
                height: element.height/element.model.count
                x:0
                y:height * index

                MouseArea
                {
                    id: mouseArea1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onClicked:
                    {
                        element.indiceAffiche=index
                        element.changeAffichage(index)
                    }
                    Rectangle {
                        id: rectangle4
                        color:indiceAffiche==index?"#262626":"transparent"
                        anchors.bottomMargin: 1
                        anchors.fill: parent
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Text {
                        id: element2
                        text: _nom
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pixelSize: 12
                        color:indiceAffiche==index?"white":"white"
                    }

                    Rectangle {
                        id: rectangle2
                        height: 1
                        color: "white"
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.top: rectangle4.bottom
                        anchors.topMargin: 0
                        Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                        Layout.preferredHeight: 1
                        Layout.fillWidth: true
                    }

                }
            }

        }

    }
}
