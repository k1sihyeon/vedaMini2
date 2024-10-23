#include "connectwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // w.show();

    ConnectWidget cw;
    cw.show();

    // 서버 연결 -> 로그인 / 회원가입 -> 채팅
    // connection -> login / register -> widget

    return a.exec();
}
