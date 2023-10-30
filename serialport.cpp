#include "serialport.h"

SerialPort::SerialPort(QObject *parent)
    : QObject{parent}
{

}

SerialPort::~SerialPort()
{
    if(m_serialPort)
    {
        disconnectPixhawk();
    }
}

void SerialPort::disconnectPixhawk()
{
    m_serialPort->close();
    delete m_serialPort;
    qDebug() << "Serial Port Is closed and deleted.";
    setConnectionStatus("DISCONNECT");
}

bool SerialPort::connectPixhawk(const QString &portName)
{
    if (connectionStatus() != "SUCCESS") {
        m_serialPort = new QSerialPort();
        qDebug() << "Serial Port Is created.";

        m_serialPort->setPortName(portName);
        m_serialPort->setBaudRate(QSerialPort::Baud57600);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setParity(QSerialPort::Parity::NoParity);
        m_serialPort->setStopBits(QSerialPort::StopBits::OneStop);
        m_serialPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
        m_serialPort->open(QIODevice::ReadWrite);

        if (m_serialPort->isOpen())
        {
            qDebug() << "Connected On Port " << portName;
            qDebug() << m_serialPort->error();
            setConnectionStatus("SUCCESS");

            setMavlinkMsg(pwmValue2, servoIndex1);
            sendMessage();
            setMavlinkMsg(pwmValue2, servoIndex2);
            sendMessage();

            qDebug() << "Serial port: " << m_serialPort;
            return true;
        }
        else
        {
            qDebug() << "Connection Error";
            qDebug() << m_serialPort->error();
            disconnectPixhawk();
            return false;
        }
    } else {
        disconnectPixhawk();
        return false;
    }
}

void SerialPort::setMavlinkMsg(uint16_t pwmValue, uint8_t servoIndex)
{
    mavlink_msg_command_long_pack(systemId, componentId, &msg,
                                  systemId,                       // Target system ID
                                  componentId,                    // Target component ID
                                  MAV_CMD_DO_SET_SERVO,           // Command ID for setting a servo
                                  0,                              // Confirmation
                                  servoIndex,                     // Servo index
                                  pwmValue,                       // PWM value for 0 degrees
                                  0, 0, 0, 0, 0);                 // Parameters 2-7 not used
}

void SerialPort::sendMessage()
{
    // Serialize the message and send it over the serial port
    len = mavlink_msg_to_send_buffer(buf, &msg);
    m_serialPort->write(reinterpret_cast<const char*>(buf), len);
    m_serialPort->flush();
}

bool SerialPort::toggleServo()
{
    if (servoStatus != "ON")
    {
        setMavlinkMsg(pwmValue1, servoIndex1);
        sendMessage();
        setMavlinkMsg(pwmValue1, servoIndex2);
        sendMessage();

        setServoStatus("ON");

        return true;
    } else
    {
        setMavlinkMsg(pwmValue2, servoIndex1);
        sendMessage();
        setMavlinkMsg(pwmValue2, servoIndex2);
        sendMessage();

        setServoStatus("OFF");

        return false;
    }
}

QString SerialPort::getServoStatus() const
{
    return servoStatus;
}

void SerialPort::setServoStatus(const QString &newServoStatus)
{
    servoStatus = newServoStatus;
}

QString SerialPort::portName() const
{
    return m_portName;
}

void SerialPort::setPortName(const QString &newPortName)
{
    m_portName = newPortName;
}

QString SerialPort::connectionStatus() const
{
    return m_connectionStatus;
}

void SerialPort::setConnectionStatus(const QString &newConnectionStatus)
{
    m_connectionStatus = newConnectionStatus;
}
