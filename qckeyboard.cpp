#include "qckeyboard.h"

QCKeyboard::QCKeyboard(QObject *parent) : QObject(parent) {
    #ifdef Q_OS_UNIX
        struct termios ts;
        tcgetattr(0, &ts);
        ts.c_lflag &= ~ICANON;
        tcsetattr(0,TCSANOW, &ts);
    #endif
    connect(&Timer, SIGNAL(timeout()), this, SLOT(timeout()));
    Timer.start(100);
}

QCKeyboard::~QCKeyboard() {}

#ifdef Q_OS_UNIX
    int QCKeyboard::kbhit(void) {
        struct timeval tv;
        fd_set read_fd;
        tv.tv_sec= 0;
        tv.tv_usec= 0;
        FD_ZERO(&read_fd);
        FD_SET(0, &read_fd);
        if (select(1, &read_fd, NULL, NULL, &tv)== -1) return 0;
        if (FD_ISSET(0, &read_fd)) return 1;
        return 0;
    }
#endif

void QCKeyboard::timeout() {
    Timer.stop();
    QString BufferIn;
    #ifdef Q_OS_WIN
        while (kbhit()!= 0) {
            int Value= _getch();
            if (Value!= 0) BufferIn.append(Value);
        }
    #endif
    #ifdef Q_OS_UNIX
        while (kbhit()!= 0) BufferIn.append(getchar());
    #endif
    if (BufferIn.length()> 0) emit OnData(BufferIn);
    Timer.start(500);
}
