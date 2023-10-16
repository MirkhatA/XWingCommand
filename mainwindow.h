#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QDebug>
#include <QtSerialPort/QSerialPort>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
private:
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
