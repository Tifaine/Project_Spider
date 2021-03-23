#include "gestionactions.h"

GestionActions::GestionActions(QObject *parent) : QObject(parent)
{

}

void GestionActions::init(GestionDyna *gestDyna)
{
    listActions.clear();
    listActions.append(new Action("Départ"));
    listActions.append(new Action("Fin"));
    listActions.append(new Action("Sequence"));
    listActions.last()->addParam();
    listActions.last()->setParamName(0, "Nom");
    listActions.last()->setParamDefaultValue(0, "init");

    listActions.append(new Action("SetDyna"));
    listActions.last()->addParam();
    listActions.last()->setParamName(0, "ID");
    listActions.last()->setParamDefaultValue(0, "0");
    listActions.last()->addParam();
    listActions.last()->setParamName(1, "Value");
    listActions.last()->setParamDefaultValue(1, "0");
    listActions.last()->addParam();
    listActions.last()->setParamName(2, "Vitesse");
    listActions.last()->setParamDefaultValue(2, "500");

    listActions.append(new Action("GetDyna"));
    listActions.last()->setBlocante(true);
    listActions.last()->addParam();
    listActions.last()->setParamName(0, "ID");
    listActions.last()->setParamDefaultValue(0, "0");
    listActions.last()->addParam();
    listActions.last()->setParamName(1, "Value");
    listActions.last()->setParamDefaultValue(1, "0");

    for(int i = 0; i < gestDyna->getNbDyna(); i++)
    {
        listActions.at(3)->addAlias(0);
        listActions.at(3)->setAliasName(0, i, QString::number(gestDyna->getDynaAtIndex(i)->id));
        listActions.at(4)->addAlias(0);
        listActions.at(4)->setAliasName(0, i, QString::number(gestDyna->getDynaAtIndex(i)->id));
    }
    qDebug()<<"LKa "<<getNbAction();
    emit finChargementAllActions();
}

int GestionActions::getNbAction()
{
    return listActions.length();
}

QString GestionActions::getNomAction(int indice)
{
    return listActions.at(indice)->getNom();
}
