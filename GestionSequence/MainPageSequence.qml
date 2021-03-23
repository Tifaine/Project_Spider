import QtQuick 2.0
import "../Composants"

Item {
    id: item1
    width:1500
    height:800



    Connections
    {
        target:gestActions
        function onFinChargementAllActions()
        {
            console.log("Wo")
            listActionSequence.clear()
            for(var i = 0; i < gestActions.getNbAction(); i++)
            {
                listActionSequence.append({"_x":5,
                                              "_y":listActionSequence.count * 45,
                                              "_height":40 , "_width":110,
                                              "_nom":gestActions.getNomAction(i) ,
                                              "index" : listActionSequence.count,
                                              "_color":"#00ffffff"})
            }
        }
    }

    ListModel
    {
        id:listActionSequence
        ListElement{ _x:0 ; _y:0; _height:40 ; _width:110; _nom:"Deplacement" ; index : 0; _color:"#00ffffff";}
    }

    FlickableList
    {
        id:flickableList
        width: 120
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        model:listActionSequence
        contentWidth: 5000; contentHeight: 100
        onClickGauche:
        {
            console.log("gauche", indice, nom)
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


}
