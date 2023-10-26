#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>

#include <mavlink/common/mavlink.h>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit            SerialPort(QObject *parent = nullptr);
    ~SerialPort();



    QString             getServoStatus() const;
    void                setServoStatus(const QString &newServoStatus);

    QString             portName() const;
    void                setPortName(const QString &newPortName);

    QString             connectionStatus() const;
    void                setConnectionStatus(const QString &newConnectionStatus);

public slots:
    bool                connectPixhawk(const QString &portName);
    void                disconnectPixhawk();
    void                sendMessage();
    void                setMavlinkMsg(uint16_t pwmValue);
    bool                toggleServo();

signals:

private:
    QSerialPort         *m_serialPort;

    QString             m_portName;
    QString             m_connectionStatus;

    uint8_t             systemId        =   1;                  // System ID
    uint8_t             componentId     =   MAV_COMP_ID_SERVO1; // Component ID for the servo
    uint8_t             servoIndex      =   5;                  // MAIN OUT 5
    uint8_t             confirmation    =   0;                  // Confirmation

    uint16_t            pwmValue1       =   1000;               // 0 degrees
    uint16_t            pwmValue2       =   2000;               // 180 degrees

    mavlink_message_t   msg;
    QString             servoStatus     =   "OFF";
};

#endif // SERIALPORT_H
