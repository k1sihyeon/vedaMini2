#include "connectwidget.h"
#include "loginwidget.h"

#include <QTcpSocket>
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
#include <QLineEdit>

ConnectWidget::ConnectWidget(QWidget *parent) : QWidget{parent}
{
    // 서버 연결 소켓 생성
    serverSocket = new QTcpSocket(this);

    // 서버 주소 입력줄
    serverAddress = new QLineEdit(this);
    serverAddress->setText("127.0.0.1");

    // 서버 IP 주소 입력 형식 제한
    QRegularExpression re("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$|");

    QRegularExpressionValidator validator(re);
    serverAddress->setValidator(&validator);
    serverAddress->setPlaceholderText("Server IP Address");

    // 서버 포트 입력줄
    serverPort = new QLineEdit(this);
    serverPort->setInputMask("00000;_");
    serverPort->setPlaceholderText("Server Port Number");

    // 서버 연결 버튼
    QPushButton* connectBtn = new QPushButton("connect", this);

    connect(serverPort, SIGNAL(returnPressed()), SLOT(connectAct()));
    connect(connectBtn, SIGNAL(clicked()), SLOT(connectAct()));

    // 서버 :horizon 가로 레이아웃
    QHBoxLayout* serverLayout = new QHBoxLayout;
    serverLayout->addStretch(1);
    serverLayout->addWidget(serverAddress);
    serverLayout->addWidget(serverPort);
    serverLayout->addWidget(connectBtn);

    setLayout(serverLayout);

    // 서버 소켓 설정 - signal, slot
    connect(serverSocket, &QAbstractSocket::errorOccurred, [=] {
        qDebug() << serverSocket->errorString();
    });
}

QTcpSocket* ConnectWidget::getServerSocket() {
    return serverSocket;
}

void ConnectWidget::connectAct() {
    serverSocket->connectToHost(serverAddress->text(), serverPort->text().toInt());

    if (serverSocket->state() == QAbstractSocket::ConnectingState) {
        this->hide();
        LoginWidget* lw = new LoginWidget();
        lw->show();
    }

    else {
        QMessageBox::warning(this, "Connect Error", "Cannot Connect Server. \nCheck Server Address and Port!");
        serverAddress->clear();
        serverPort->clear();
    }
}
