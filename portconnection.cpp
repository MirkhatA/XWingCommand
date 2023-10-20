#include "portconnection.h"
#include <mavlink/mavlink_helpers.h>
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
        portStatus("Serial Port Is connected");
        qDebug() << "Serial Port Is connected";
        qDebug() << serial->error();
    }
    else
    {
        portStatus("Serial Port is not connected");
        qDebug() << "Serial Port is not connected";
        qDebug() << serial->error();
    }
}

void PortConnection::toggleServo()
{
    qDebug() << "Toggling servo";

    if (serial->isOpen()) {
        uint8_t systemId = 1; // System ID
        uint8_t componentId = MAV_COMP_ID_SERVO1; // Component ID for the servo

        uint8_t servoIndex = 5; // MAIN OUT 5

        uint16_t pwmValue1 = 1000; // 0 degrees
        uint16_t pwmValue2 = 2000; // 180 degrees

        mavlink_message_t msg;
        mavlink_msg_command_long_pack(systemId, componentId, &msg,
                                      systemId,                       // Target system ID
                                      componentId,                    // Target component ID
                                      MAV_CMD_DO_SET_SERVO,           // Command ID for setting a servo
                                      0,                              // Confirmation
                                      servoIndex,                     // Servo index
                                      pwmValue1,                      // PWM value for 0 degrees
                                      0, 0, 0, 0, 0);                 // Parameters 2-7 not used

        // Serialize the message and send it over the serial port
        uint8_t buf[MAVLINK_MAX_PACKET_LEN];
        uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
        serial->write(reinterpret_cast<const char*>(buf), len);
        serial->flush();

        len = mavlink_msg_to_send_buffer(buf, &msg);
        serial->write(reinterpret_cast<const char*>(buf), len);
        serial->flush();

        portStatus("Servo toggled");
        qDebug() << "Servo toggled";
    } else {
        portStatus("Serial Port is not connected");
        qDebug() << "Serial Port is not connected";
    }
}
