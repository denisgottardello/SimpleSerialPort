#ifndef QCKEYBOARD_H
#define QCKEYBOARD_H

#include <QtCore/QCoreApplication>
#include "QTimer"
#ifdef Q_OS_WIN
    #include "conio.h"
#endif
#ifdef Q_OS_UNIX
    #include "stdio.h"
    #include <termios.h>
    #include <sys/ioctl.h>
#endif

class QCKeyboard : public QObject
{
    Q_OBJECT

public:
    QCKeyboard(QObject *parent);
    ~QCKeyboard();

signals:
    void OnData(QString Data);

private:
    QTimer Timer;
    #ifdef Q_OS_UNIX
        int kbhit();
    #endif

private slots:
    void timeout();

};

#endif // QCKEYBOARD_H
