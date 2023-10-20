#ifndef PORTCONNECTION_H
#define PORTCONNECTION_H

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QString>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QUdpSocket>
#include <QThread>

#include <mavlink/common/mavlink.h>

class PortConnection : public QObject
{
    Q_OBJECT
public:
    PortConnection();
    ~PortConnection();

signals:
    void portStatus(QString s);

public slots:
    void onConnectToPort();

    void toggleServo();

private:
    QSerialPort *serial;
};

#endif // PORTCONNECTION_H
