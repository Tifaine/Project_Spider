#include "gestiondyna.h"
#include <QThread>
GestionDyna::GestionDyna(QObject *parent) : QObject(parent)
{
    /*init();
    updateListDyna(1, 43);
    updateListDyna(1, 43);

    for(int i = 0; i < listIdDyna.size();i++)
    {
        qDebug()<< listIdDyna.at(i)->id<<" "<<listIdDyna.at(i)->position<<" "<<listIdDyna.at(i)->vitesse;
    }

    uint8_t dxl_error = 0;
    packetHandler->write2ByteTxRx(portHandler, 10, ADDR_MX_GOAL_POSITION, 500, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 20, ADDR_MX_GOAL_POSITION, 500, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 30, ADDR_MX_GOAL_POSITION, 500, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 40, ADDR_MX_GOAL_POSITION, 500, &dxl_error);

    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 11, ADDR_MX_GOAL_POSITION, 350, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 21, ADDR_MX_GOAL_POSITION, 350, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 31, ADDR_MX_GOAL_POSITION, 350, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 41, ADDR_MX_GOAL_POSITION, 350, &dxl_error);

    QThread::msleep(2500);
    packetHandler->write2ByteTxRx(portHandler, 12, ADDR_MX_GOAL_POSITION, 500, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 22, ADDR_MX_GOAL_POSITION, 500, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 32, ADDR_MX_GOAL_POSITION, 500, &dxl_error);
    QThread::msleep(50);
    packetHandler->write2ByteTxRx(portHandler, 42, ADDR_MX_GOAL_POSITION, 500, &dxl_error);*/
}

GestionDyna::~GestionDyna()
{
    // Close port
    portHandler->closePort();
}

void GestionDyna::updateListDyna(int from, int to)
{
    // Try to ping the Dynamixel
    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    uint8_t dxl_error = 0;                          // Dynamixel error
    uint16_t dxl_model_number;
    uint16_t dxl_present_position = 0;
    uint16_t dxl_present_speed = 0;
    // Get Dynamixel model number
    for(int i = from; i < to; i++)
    {
        dxl_comm_result = packetHandler->ping(portHandler, i, &dxl_model_number, &dxl_error);
        if (dxl_comm_result != COMM_SUCCESS)
        {

        }
        else if (dxl_error != 0)
        {

        }
        else
        {
            dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, i, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
            QThread::msleep(50);
            dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, i, ADDR_MX_GOAL_SPEED, 512, &dxl_error);
            QThread::msleep(50);
            dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, i, ADDR_MX_PRESENT_POSITION, &dxl_present_position, &dxl_error);
            QThread::msleep(50);
            dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, i, ADDR_MX_PRESENT_SPEED, &dxl_present_speed, &dxl_error);
            QThread::msleep(50);
            if(containsID(i) == -1)
            {
                listIdDyna.append(new Dyna);
                listIdDyna.last()->id = i;
                listIdDyna.last()->position = dxl_present_position;
                listIdDyna.last()->vitesse = dxl_present_speed;
                emit newDyna(QString::number(i), QString::number(dxl_present_position));
            }
        }
    }
}

bool GestionDyna::init(QString portCom)
{
    portHandler = dynamixel::PortHandler::getPortHandler(portCom.toStdString().c_str());

    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
                       // Dynamixel model number

    // Open port
    if (portHandler->openPort())
    {
        qDebug()<<("Succeeded to open the port!\n");
    }
    else
    {
        qDebug()<<("Failed to open the port!\n");
        return false;
    }

    // Set port baudrate
    if (portHandler->setBaudRate(BAUDRATE))
    {
        qDebug()<<("Succeeded to change the baudrate!\n");
    }
    else
    {
        qDebug()<<("Failed to change the baudrate!\n");
        return false;
    }
    return true;
}

int GestionDyna::containsID(int idToTest)
{
    for(int i = 0; i < listIdDyna.size(); i++)
    {
        if(listIdDyna.at(i)->id == idToTest)
            return i;
    }
    return -1;
}

Dyna* GestionDyna::getDynaAtIndex(int index)
{
    if(index < listIdDyna.size() && index >= 0)
    {
        return listIdDyna.at(index);
    }
    return nullptr;
}

int GestionDyna::getNbDyna()
{
    return listIdDyna.size();
}

int GestionDyna::getNbPortCOMAvailable()
{
    return QSerialPortInfo::availablePorts().size();
}

QString GestionDyna::getPortComName(int indice)
{
    if(indice >= 0 && indice < QSerialPortInfo::availablePorts().size())
    {
        return QSerialPortInfo::availablePorts().at(indice).portName();
    }
    return "";
}

void GestionDyna::setValueDyna(int idDyna, int value)
{
    uint8_t dxl_error = 0;
    packetHandler->write2ByteTxRx(portHandler, idDyna, ADDR_MX_GOAL_POSITION, value, &dxl_error);
}


void GestionDyna::setSpeedDyna(int idDyna, int value)
{
    uint8_t dxl_error = 0;
    packetHandler->write2ByteTxRx(portHandler, idDyna, ADDR_MX_GOAL_SPEED, value, &dxl_error);
}

