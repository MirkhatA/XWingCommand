#ifndef PORTCONNECTION_H
#define PORTCONNECTION_H

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QString>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQmlProperty>

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

private:
    QSerialPort *serial;
};

#endif // PORTCONNECTION_H
