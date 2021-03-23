#include "action.h"

Action::Action(QString nom):
    _nom(nom),
    blocante(false)
{

}

QString Action::getNom() const
{
    return _nom;
}

void Action::setNom(const QString &value)
{
    _nom = value;
}

bool Action::isBlocante() const
{
    return blocante;
}

void Action::setBlocante(bool value)
{
    blocante = value;
    if(blocante)
    {
        listParam.insert(0, new Parametre);
        listParam.at(0)->name = "Timeout";
        listParam.at(0)->defaultValue = "10000";
    }else
    {
        listParam.removeAt(0);
    }
}

void Action::addParam()
{
    listParam.append(new Parametre);
    listParam.last()->name = "Param";
    listParam.last()->defaultValue = "default";

}

int Action::getNbParam()
{
    return listParam.size();
}

QString Action::getParamName(int indiceParam)
{
    if(indiceParam < listParam.size())
    {
        return listParam.at(indiceParam)->name;
    }
    return "Comment ?";
}

QString Action::getParamDefaultValue(int indiceParam)
{
    if(indiceParam < listParam.size())
    {
        return listParam.at(indiceParam)->defaultValue;
    }
    return "Bravo, mais t'es pas sensé voir ça, enjoy le segfault";
}


void Action::setParamName(int indiceParam, QString name)
{
    if(indiceParam < listParam.size())
    {
        listParam.at(indiceParam)->name = name;
    }
}
void Action::setParamDefaultValue(int indiceParam, QString value)
{
    if(indiceParam < listParam.size())
    {
        listParam.at(indiceParam)->defaultValue = value;
    }
}

void Action::deleteParametre(int indiceParam)
{
    if(indiceParam < listParam.size())
    {
        listParam.removeAt(indiceParam);
    }
}

void Action::addAlias(int indiceParam)
{
    if(indiceParam < listParam.size())
    {
        listParam.at(indiceParam)->listAlias.append(new Alias);
        listParam.at(indiceParam)->listAlias.last()->name = "Alias";
        listParam.at(indiceParam)->listAlias.last()->value = "value";
    }
}

int Action::getNbAlias(int indiceParam)
{
    if(indiceParam < listParam.size())
    {
        return listParam.at(indiceParam)->listAlias.size();
    }
    return 0;
}

QString Action::getAliasName(int indiceParam, int indiceAlias)
{
    if(indiceParam < listParam.size())
    {
        if(indiceAlias < listParam.at(indiceParam)->listAlias.size())
        {
            return listParam.at(indiceParam)->listAlias.at(indiceAlias)->name;
        }
    }
    return "You died.";
}

QString Action::getAliasValue(int indiceParam, int indiceAlias)
{
    if(indiceParam < listParam.size())
    {
        if(indiceAlias < listParam.at(indiceParam)->listAlias.size())
        {
            return listParam.at(indiceParam)->listAlias.at(indiceAlias)->value;
        }
    }
    return "I hear cheh in my oreillette";
}

void Action::setAliasName(int indiceParam, int indiceAlias, QString name)
{
    if(indiceParam < listParam.size())
    {
        if(indiceAlias < listParam.at(indiceParam)->listAlias.size())
        {
            listParam.at(indiceParam)->listAlias.at(indiceAlias)->name = name;
        }
    }
}

void Action::setAliasValue(int indiceParam, int indiceAlias, QString value)
{
    if(indiceParam < listParam.size())
    {
        if(indiceAlias < listParam.at(indiceParam)->listAlias.size())
        {
            listParam.at(indiceParam)->listAlias.at(indiceAlias)->value = value;
        }
    }
}

void Action::deleteAlias(int indiceParam, int indiceAlias)
{
    if(indiceParam < listParam.size())
    {
        if(indiceAlias < listParam.at(indiceParam)->listAlias.size())
        {
            listParam.at(indiceParam)->listAlias.removeAt(indiceAlias);
        }
    }
}

void Action::save()
{
    QFile saveFile("data/Actions/"+ getNom() +".json");
    if(!saveFile.open(QIODevice::ReadWrite))
    {
        qDebug()<<"Failed ! "<<saveFile.fileName();
    }else
    {
        saveFile.flush();
        saveFile.resize(0);
        QJsonObject saveObject;
        saveObject["nomAction"] = _nom;
        saveObject["blocante"] = blocante;

        QJsonArray arrayParam;
        QString nomParam("nomParam");
        QString defaultValue("defaultValue");
        for(auto item : listParam)
        {
            QJsonObject item_data;
            item_data.insert(nomParam, QJsonValue(item->name));
            item_data.insert(defaultValue, QJsonValue(item->defaultValue));

            QJsonArray arrayAlias;
            QString nomAlias("nomAlias");
            QString valueAlias("valueAlias");
            QString aliasArray("aliasArray");
            for(auto itemAlias : item->listAlias)
            {
                QJsonObject item_Alias;
                item_Alias.insert(nomAlias, QJsonValue(itemAlias->name));
                item_Alias.insert(valueAlias, QJsonValue(itemAlias->value));

                arrayAlias.push_back(QJsonValue(item_Alias));
            }
            item_data.insert(aliasArray, QJsonValue(arrayAlias));

            arrayParam.push_back(QJsonValue(item_data));
        }

        saveObject["paramArray"] = arrayParam;

        QJsonDocument saveDoc(saveObject);
        saveFile.write(saveDoc.toJson());
    }
    saveFile.close();
}

void Action::loadAction(QString nameFile)
{
    QFile loadFile(nameFile);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Failed ! "<<loadFile.fileName();
    }else
    {
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        QJsonObject json = loadDoc.object();
        if(json.contains("nomAction") )
        {
            setNom(json["nomAction"].toString());
        }
        if(json.contains("blocante") )
        {
            blocante = json["blocante"].toBool();
        }
        if(json.contains("paramArray") )
        {
            QJsonArray array = json["paramArray"].toArray();
            foreach (const QJsonValue & v, array)
            {
                addParam();
                QJsonObject obj = v.toObject();
                if(obj.contains("nomParam") )
                {
                    setParamName(getNbParam()-1, obj["nomParam"].toString());
                }
                if(obj.contains("defaultValue") )
                {
                    setParamDefaultValue(getNbParam()-1, obj["defaultValue"].toString());
                }
                if(obj.contains("aliasArray") )
                {
                    QJsonArray arrayAlias = obj["aliasArray"].toArray();
                    foreach (const QJsonValue & w, arrayAlias)
                    {
                        addAlias(getNbParam()-1);
                        QJsonObject objAlias = w.toObject();
                        setAliasName(getNbParam()-1, getNbAlias(getNbParam()-1)-1, objAlias.value("nomAlias").toString());
                        setAliasValue(getNbParam()-1, getNbAlias(getNbParam()-1)-1, objAlias.value("valueAlias").toString());
                    }
                }
            }
        }
        loadFile.close();
    }
}

void Action::toString()
{
    qDebug()<<"Action : "<<getNom();
    for(Parametre * param : listParam)
    {
        qDebug()<<param->name<<" "<<param->defaultValue;
    }
    qDebug()<<"liste des Peres :";
    for(Action * act : listPeres)
    {
        qDebug()<<act->getNom();
    }

    qDebug()<<"liste des Filles :";
    for(Action * act : listFilles)
    {
        qDebug()<<act->getNom();
    }

    qDebug()<<"liste des Timeout :";
    for(Action * act : listTimeout)
    {
        qDebug()<<act->getNom();
    }
}

void Action::addFille(Action * fille)
{
    listFilles.append(fille);
}

void Action::addPapa(Action * papa)
{
    listPeres.append(papa);
}

void Action::addTimeout(Action * timeout)
{
    listTimeout.append(timeout);
}

QList<Action *> Action::getListPere()
{
    return listPeres;
}

QList<Action *> Action::getListFille()
{
    return listFilles;
}

QList<Action *> Action::getListTimeout()
{
    return listTimeout;
}

