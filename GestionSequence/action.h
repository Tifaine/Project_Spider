#ifndef ACTION_H
#define ACTION_H

/*
 *
 *  Dans notre robot, nous utilisons des actions pour le faire fonctionner.
 * Tout ce que peut faire le robot est basé sur le concept d'action.
 * Par exemple, un déplacement du robot à une position x,y est une action,
 * demander à un servomoteur d'aller à une position avec une vitesse donnée est une action...
 * Chaque action va donc avoir un nom et une liste de paramètres qui vont devoir être interprété par le robot.
 *
 */

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

typedef struct Alias
{
    QString name;
    QString value;
}Alias;

typedef struct Parametre
{
    QString name;
    QString defaultValue;
    QList <Alias *> listAlias;
}Parametre;

class Action
{
public:
    Action(QString nom);

    QString getNom() const;
    void setNom(const QString &value);

    bool isBlocante() const;
    void setBlocante(bool value);

    void addParam();
    int getNbParam();
    QString getParamName(int indiceParam);
    QString getParamDefaultValue(int indiceParam);
    void setParamName(int indiceParam, QString name);
    void setParamDefaultValue(int indiceParam, QString value);
    void deleteParametre(int indiceParam);

    /*
     * Afin de faciliter la lecture, chaque paramètre peut avoir des alias.
     * Par exemple, l'id d'un dyna peut avoir comme alias : pinceBrasGauche, BrasAxe1...
     */

    void addAlias(int indiceParam);
    int getNbAlias(int indiceParam);
    QString getAliasName(int indiceParam, int indiceAlias);
    QString getAliasValue(int indiceParam, int indiceAlias);
    void setAliasName(int indiceParam, int indiceAlias, QString name);
    void setAliasValue(int indiceParam, int indiceAlias, QString value);
    void deleteAlias(int indiceParam, int indiceAlias);

    void save();
    void loadAction(QString nameFile);

    void toString();

    void addFille(Action * fille);
    void addPapa(Action * papa);
    void addTimeout(Action * timeout);

    QList<Action *> getListPere();
    QList<Action *> getListFille();
    QList<Action *> getListTimeout();

private:
    QString _nom;
    bool blocante;
    QList<Parametre *> listParam;
    QList<Action *> listFilles;
    QList<Action *> listPeres;
    QList<Action *> listTimeout;

};

#endif // ACTION_H
