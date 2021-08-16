#include "qcserialportmanager.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

QCSerialPortManager::QCSerialPortManager(QObject *parent) : QObject(parent) {
    qDebug() << tr("QCSerialPortManager::QCSerialPortManager()");
    Keyboard= new QCKeyboard(parent);
    connect(Keyboard, SIGNAL(OnData(QString)), this, SLOT(OnData(QString)));
    SerialPort= new QSerialPort(this);
    SerialPort->setPortName(ArgumentGet("PortName", "ttyS0"));
    SerialPort->setBaudRate(ArgumentGet("BaudRate", "9600").toInt());
    SerialPort->setDataBits(QSerialPort::Data8);
    SerialPort->setParity(QSerialPort::NoParity);
    SerialPort->setStopBits(QSerialPort::OneStop);
    SerialPort->setFlowControl(QSerialPort::NoFlowControl);
    if (SerialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to" << SerialPort->portName();
        connect(SerialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(error(QSerialPort::SerialPortError)));
        connect(SerialPort, SIGNAL(readyRead()), this, SLOT(readyRead()));
    } else qDebug() << "Error:" << SerialPort->portName() << SerialPort->errorString();
}

QCSerialPortManager::~QCSerialPortManager() {
    delete Keyboard;
    delete SerialPort;
    qDebug() << tr("QCSerialPortManager::~QCSerialPortManager()");
}

QString QCSerialPortManager::ArgumentGet(QString Argument, QString DefaultValue) {
    for (int count= 0; count< QCoreApplication::arguments().count(); count++) {
        if (QCoreApplication::arguments().at(count).startsWith(Argument+ "=")) {
            QStringList QSLValues= QCoreApplication::arguments().at(count).split("=");
            if (QSLValues.count()> 1) return QSLValues.at(1);
        }
    }
    return DefaultValue;
}

void QCSerialPortManager::error(QSerialPort::SerialPortError ) {
    qDebug() << "Serial Port error:" << SerialPort->errorString();
    OnData("q");
}

void QCSerialPortManager::OnData(QString Data) {
    /*if (Data.compare("q", Qt::CaseInsensitive)== 0) QCoreApplication::instance()->quit();
    else */SerialPort->write(Data.toLatin1());
}

void QCSerialPortManager::readyRead() {
    QString DataIn= SerialPort->readAll();
    for (int count= 0; count< DataIn.size(); count++) std::cout << DataIn.at(count).toLatin1();
}

void QCSerialPortManager::SerialPortDump() {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString StringOut= QObject::tr("Port:")+ info.portName()+ "\n"
                + QObject::tr("Location:")+ info.systemLocation()+ "\n"
                + QObject::tr("Description:")+ info.description()+ "\n"
                + QObject::tr("Manufacturer:")+ info.manufacturer()+ "\n"
                + QObject::tr("Serial number:")+ info.serialNumber()+ "\n"
                + QObject::tr("Vendor Identifier:")+ (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString())+ "\n"
                + QObject::tr("Product Identifier:")+ (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString())+ "\n"
                + QObject::tr("Busy:")+ (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No"))+ "\n";
        qDebug() << StringOut;
    }
}
