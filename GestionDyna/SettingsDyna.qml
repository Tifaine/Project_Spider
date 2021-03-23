import QtQuick 2.0
import QtQuick.Controls 2.15
import "../Composants"

Item {
    id: item1
    width:1500
    height:800
    property bool isConnected:false
    Component.onCompleted: listDyna.clear()

    Text {
        id: textPortCOM
        color: "#ffffff"
        text: qsTr("Port COM : ")
        anchors.left: parent.left
        anchors.top: parent.top
        font.pixelSize: 12
        font.bold: true
        minimumPixelSize: 14
        anchors.leftMargin: 20
        anchors.topMargin: 20
    }

    Connections
    {
        target: gestDyna
        function onNewDyna(id, pos)
        {
            console.log(id, pos)
            listDyna.append({"_x": 5 , "_y": listDyna.count * 50,
                                "_height":40 , "_width":110, _nom:("ID : "+id +" pos : "+ pos), _id:id, _pos:pos,
                                index:listDyna.count, _color:"#00ffffff"})
        }
    }

    CustomComboBox {
        id: cbPortCom
        x:10
        width:180
        height:30
        anchors.top:parent.top
        anchors.topMargin: 13
        anchors.left: textPortCOM.right
        anchors.leftMargin: 10

        Component.onCompleted:
        {
            for(var i = 0; i < gestDyna.getNbPortCOMAvailable(); i++)
            {
                cbPortCom.addItem(gestDyna.getPortComName(i), gestDyna.getPortComName(i));
            }
        }
    }

    Button {
        id: buttonConnect
        width: 75
        height: 40
        text: qsTr("Connecter")
        anchors.left: cbPortCom.right
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 7

        contentItem: Text {
            text: buttonConnect.text
            font: buttonConnect.font
            opacity: enabled ? 1.0 : 0.3
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle
        {
            color:buttonConnect.pressed?Qt.darker("#22ffffff" ,1.2):"#22ffffff"
            radius: 10
            border.color: "#333"
            anchors.fill: parent
            border.width: 1
        }

        onClicked:
        {
            isConnected = gestDyna.init(cbPortCom.text)
        }
    }

    Text {
        visible:isConnected
        id: textScan
        color: "#ffffff"
        text: qsTr("Scan Dyna")
        anchors.left: buttonConnect.right
        anchors.top: parent.top
        font.pixelSize: 12
        font.bold: true
        anchors.leftMargin: 50
        anchors.topMargin: 20
    }

    Text {
        visible:isConnected
        id: textTo
        color: "#ffffff"
        text: qsTr("De :")
        anchors.left: textScan.right
        anchors.top: parent.top
        font.pixelSize: 12
        font.bold: true
        anchors.leftMargin: 15
        anchors.topMargin: 20
    }

    TextField {
        visible:isConnected
        id: tfTo
        width: 35
        height: 30
        text: "0"
        anchors.left: textTo.right
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        anchors.leftMargin: 5
        anchors.topMargin: 12
        placeholderText: qsTr("0")
        color: "white"
        background: Rectangle
        {
            color:"#22ffffff"
            radius: 10
            border.color: "#333"
            anchors.fill: parent
            border.width: 1
        }
    }

    Text {
        visible:isConnected
        id: textFrom
        color: "#ffffff"
        text: qsTr(" à :")
        anchors.left: tfTo.right
        anchors.top: parent.top
        font.pixelSize: 12
        anchors.leftMargin: 10
        anchors.topMargin: 20
        font.bold: true
    }

    TextField {
        visible:isConnected
        id: tfFrom
        width: 35
        height: 30
        text: "255"
        anchors.left: textFrom.right
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        anchors.leftMargin: 5
        anchors.topMargin: 12
        placeholderText: qsTr("255")
        color: "white"
        background: Rectangle
        {
            color:"#22ffffff"
            radius: 10
            border.color: "#333"
            anchors.fill: parent
            border.width: 1
        }
    }

    Button {
        visible:isConnected
        id: buttonScan
        width: 59
        height: 40
        text: qsTr("Scan")
        anchors.left: tfFrom.right
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 7

        contentItem: Text {
            text: buttonScan.text
            font: buttonScan.font
            opacity: enabled ? 1.0 : 0.3
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle
        {
            color:buttonScan.pressed?Qt.darker("#22ffffff" ,1.2):"#22ffffff"
            radius: 10
            border.color: "#333"
            anchors.fill: parent
            border.width: 1
        }
        onClicked:
        {
            buttonScan.enabled = false
            gestDyna.updateListDyna(tfTo.text, tfFrom.text)
            buttonScan.enabled = true
        }
    }

    ListModel
    {
        id:listDyna
        ListElement{ _x:0 ; _y:0; _height:40 ; _width:110; _nom:"Deplacement" ; index : 0; _color:"#00ffffff"; _id:"-1"; _pos:"-1"}
    }

    property int idDynaChose:-1

    FlickableList
    {
        id:flickableList
        width: 120
        anchors.left: parent.left
        anchors.top: textPortCOM.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.leftMargin: 10
        anchors.topMargin: 50
        model:listDyna
        contentWidth: 5000; contentHeight: 100
        onClickGauche:
        {
            idDynaChose = -1
            dial.value = listDyna.get(indice)._pos
            parent.idDynaChose = listDyna.get(indice)._id
            console.log(parent.idDynaChose)
        }
        onClickDroit:
        {
            console.log("droit", indice, nom)
        }
        onDoubleClick:
        {
            console.log("double", indice, nom)
        }
    }

    Dial {
        id: dial
        visible:idDynaChose !== -1
        anchors.left: flickableList.right
        anchors.top: buttonScan.bottom
        anchors.leftMargin: 60
        anchors.topMargin: 75
        stepSize: 1
        to: 1024
        onValueChanged:
        {
            if(idDynaChose !== -1)
            {
                gestDyna.setValueDyna(idDynaChose, value)
            }
        }
    }

    Dial {
        id: dialVitesse
        visible:idDynaChose !== -1
        anchors.left: dial.right
        anchors.top: buttonScan.bottom
        anchors.leftMargin: 50
        anchors.topMargin: 75
        stepSize: 1
        to: 1024
        onValueChanged:
        {
            if(idDynaChose !== -1)
            {
                gestDyna.setSpeedDyna(idDynaChose, value)
            }
        }
    }
}
