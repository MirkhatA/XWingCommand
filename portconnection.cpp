#include "portconnection.h"

PortConnection::PortConnection()
{


}

PortConnection::~PortConnection()
{
    serial->close();

    qDebug() << "Serial Port is closed";

    delete serial;
}

void PortConnection::onConnectToPort()
{
    serial = new QSerialPort();
    serial->setPortName("COM13");
    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::Parity::NoParity);
    serial->setStopBits(QSerialPort::StopBits::OneStop);
    serial->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

    if (serial->isOpen())
    {
        qDebug() << "Serial Port Is connected";
        qDebug() << serial->error();
    }
    else
    {
        qDebug() << "Serial Port is not connected";
        qDebug() << serial->error();
    }
}

