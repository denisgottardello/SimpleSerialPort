#include <QCoreApplication>
#include "qcserialportmanager.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc== 1) {
        std::cout << "Please usage:" << std::endl;
        std::cout << "PortName=com1 for com1" << std::endl;
        std::cout << "BaudRate=9600 for baud rate at 9600" << std::endl;
        std::cout << "Press ctrl-c to quit" << std::endl;
    } else {
        QCoreApplication a(argc, argv);
        QCSerialPortManager b(&a);

        return a.exec();
    }
    return 0;
}
