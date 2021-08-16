#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QtSerialPort/QSerialPort>
#include "QCoreApplication"
#include "qckeyboard.h"
#include <iostream>

class QCSerialPortManager : public QObject
{
    Q_OBJECT

public:
    explicit QCSerialPortManager(QObject *parent = nullptr);
    ~QCSerialPortManager();

private slots:
    void error(QSerialPort::SerialPortError error);
    void OnData(QString Data);
    void readyRead();
    void SerialPortDump();

private:
    QCKeyboard *Keyboard= nullptr;
    QSerialPort *SerialPort= nullptr;
    QString ArgumentGet(QString Argument, QString DefaultValue= "");

};

#endif // SERIALPORTMANAGER_H
