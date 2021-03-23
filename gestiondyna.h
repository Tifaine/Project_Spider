#ifndef GESTIONDYNA_H
#define GESTIONDYNA_H

#include <QObject>
#include <QDebug>
#include <QList>
#include "dynamixel_sdk.h"
#include <QtSerialPort/QSerialPortInfo>

#define PROTOCOL_VERSION                1.0
#define BAUDRATE                        1000000
#define ADDR_MX_TORQUE_ENABLE           24                  // Control table address is different in Dynamixel model
#define ADDR_MX_GOAL_POSITION           30
#define ADDR_MX_GOAL_SPEED              32
#define ADDR_MX_PRESENT_POSITION        36
#define ADDR_MX_PRESENT_SPEED           38
#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque

typedef struct Dyna
{
    int id;
    int position;
    int vitesse;
}Dyna;

class GestionDyna : public QObject
{
    Q_OBJECT
public:
    explicit GestionDyna(QObject *parent = nullptr);
    ~GestionDyna();

public slots:
    void updateListDyna(int from, int to);
    bool init(QString portCom);

    //Test if ID is contained in listIdDyna, return index in the list, -1 if not there.
    int containsID(int idToTest);

    Dyna* getDynaAtIndex(int index);
    int getNbDyna();

    int getNbPortCOMAvailable();
    QString getPortComName(int indice);

    void setValueDyna(int idDyna, int value);
    void setSpeedDyna(int idDyna, int value);

private:

signals:
    void newDyna(QString id, QString pos);

private:
    QList<Dyna*> listIdDyna;
    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;
};

#endif // GESTIONDYNA_H
