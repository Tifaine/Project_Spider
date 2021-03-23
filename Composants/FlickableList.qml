import QtQuick 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12

Item {
    id:itemParent
    property int contentWidth: 5000
    property int contentHeight: 100
    property bool vertical:false
    property var model
    signal clickGauche(int indice, string nom)
    signal clickDroit(int indice, string nom)
    signal doubleClick(int indice, string nom)

    /*  Ce composant étant utilisé à plusieurs reprises, il a été créé afin de factoriser un peu le code.
        Il va permettre d'avoir une liste d'élément flickable respectant un modèle.
        Ce modèle doit être passé en paramètre.
        Il doit cependant contenir au minimum les paramètres suivants :
            int _x, int _y, int _height, int _width, string _nom, int index et enfin string _color

        Un signal est émit lorsque qu'on clique gauche, droit et double click sur un élément.
        Le signal comprendra alors l'indice et le nom de l'élément sur lequel a eu lieu l'évenement
    */

    Flickable
    {
        clip:true
        id: flickable
        height: 100
        flickableDirection: vertical===true? Flickable.VerticalFlick : Flickable.HorizontalFlick
        anchors.fill: parent
        contentWidth: itemParent.contentWidth; contentHeight: itemParent.contentHeight
        contentX: 0
        contentY:0

        ScrollBar.horizontal: ScrollBar {
            visible: !(itemParent.vertical)
            parent: flickable.parent
            anchors.left: flickable.left
            anchors.right: flickable.right
            anchors.bottom: flickable.bottom
        }

        ScrollBar.vertical: ScrollBar {
            visible: itemParent.vertical
            parent: flickable.parent
            anchors.top: flickable.top
            anchors.right: flickable.right
            anchors.bottom: flickable.bottom
        }

        Rectangle
        {
            id:rectangle5
            anchors.fill: parent
            color:"transparent"

            function updateColor(indice)
            {
                itemParent.model.setProperty(indice,"_color","#300000");
                if(behaviorSelected !== -1 && indice !== behaviorSelected)
                {
                    itemParent.model.setProperty(behaviorSelected,"_color","#00ffffff");
                }

                behaviorSelected = indice
            }

            property int behaviorSelected:-1
            Repeater
            {
                id:repeaterListAction
                model:itemParent.model
                anchors.fill: parent
                Rectangle
                {
                    id:rect
                    height: _height
                    width:  _width
                    x:      _x
                    y:      _y
                    color:  _color
                    radius: 10
                    border.color: "#ffffff"
                    border.width: 1

                    Rectangle
                    {
                        color: _color//"#0cfdfdfd"
                        radius: 10
                        anchors.right: parent.right
                        anchors.rightMargin: 1
                        anchors.left: parent.left
                        anchors.leftMargin: 1
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 3
                        anchors.top: parent.top
                        anchors.topMargin: 3
                        Text {
                            id: nomComportement
                            text: _nom
                            color:"white"
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        }

                        MouseArea
                        {
                            anchors.fill: parent
                            z:1
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            onClicked:
                            {
                                rectangle5.updateColor(index)
                                if(mouse.button === Qt.RightButton)
                                {
                                    itemParent.clickDroit(index, _nom)
                                }else
                                {
                                    itemParent.clickGauche(index, _nom)
                                }
                            }
                            onDoubleClicked:
                            {
                                rectangle5.updateColor(index)
                                itemParent.doubleClick(index, _nom)
                            }
                        }
                    }
                }
            }
        }
    }
}
