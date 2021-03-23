#ifndef GESTIONACTIONS_H
#define GESTIONACTIONS_H

#include <QObject>
#include <QList>
#include "action.h"
#include "../gestiondyna.h"

class GestionActions : public QObject
{
    Q_OBJECT
public:
    explicit GestionActions(QObject *parent = nullptr);

public slots:
    void init(GestionDyna * gestDyna);
    int getNbAction();
    QString getNomAction(int indice);

signals:
    void finChargementAllActions();
private:
    QList<Action *> listActions;

};

#endif // GESTIONACTIONS_H
