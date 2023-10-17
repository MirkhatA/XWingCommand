#ifndef PORTCONNECTION_H
#define PORTCONNECTION_H

#include <QDebug>
#include <QtSerialPort/QSerialPort>

class PortConnection : public QObject
{
    Q_OBJECT
public:
    PortConnection();
    ~PortConnection();

public slots:
    void onConnectToPort();

private:
    QSerialPort *serial;
};

#endif // PORTCONNECTION_H
