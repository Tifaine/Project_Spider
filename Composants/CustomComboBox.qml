import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Qt.labs.folderlistmodel 2.12

ComboBox {

    signal valueTextChanged(string text)
    property string text : displayText
    function addItem(nom, value)
    {
        listCustomComboBox.append({_nom:nom, value:value})
    }

    Component.onCompleted: listCustomComboBox.clear()

    ListModel
    {
        id:listCustomComboBox
        ListElement{ _nom:"x" ; value:"0"}
    }

    id: customComboBox

    model:listCustomComboBox

    currentIndex: 0
    onCurrentIndexChanged:
    {
        if(listCustomComboBox.count > currentIndex && currentIndex !== -1)
        {
            customComboBox.displayText = listCustomComboBox.get(currentIndex)._nom
            valueTextChanged(listCustomComboBox.get(currentIndex).value)
        }
    }

    delegate: ItemDelegate {
        width: customComboBox.width
        contentItem: Text {
            text: (_nom + "("+value+")")
            color: "white"
            font: customComboBox.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: customComboBox.highlightedIndex === index
        background: Rectangle {
            implicitWidth: 120
            implicitHeight: 40
            color:customComboBox.highlightedIndex === index ? "#262626" : "transparent"
        }
    }

    indicator: Canvas {
        id: canvas
        x: customComboBox.width - width - customComboBox.rightPadding
        y: customComboBox.topPadding + (customComboBox.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: customComboBox
            function onPressedChanged()
            {
                canvas.requestPaint()
            }
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = customComboBox.pressed ? "#4d0000" : "#660000";
            context.fill();
        }
    }

    contentItem: Text {
        leftPadding: 10
        rightPadding: customComboBox.indicator.width + customComboBox.spacing

        text: customComboBox.displayText
        font: customComboBox.font
        color: "white"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 40
        color:"#262626"
        border.color: customComboBox.pressed ? "#4d0000" : "#66000"
        border.width: customComboBox.visualFocus ? 2 : 1
        radius: 7
    }

    popup: Popup {
        visible:true
        y: customComboBox.height - 1
        width: customComboBox.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: customComboBox.popup.visible ? customComboBox.delegateModel : null
            currentIndex: customComboBox.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: "#4d0000"
            color:"#363636"
            radius: 7
        }
    }
}

