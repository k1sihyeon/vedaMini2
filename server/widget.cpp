#include "widget.h"

#include "../common/message.h"

#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include <QLabel>

#define BLOCK_SIZE      1024

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(this);
    QLabel* portLabel = new QLabel(this);
    QPushButton *quitBtn = new QPushButton("Quit", this);
    connect(quitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(portLabel);
    mainLayout->addWidget(label);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(clientConnect()));
    if (!server->listen()) {
        QMessageBox::critical(this, tr("Echo Server"), tr("Unable to start the server: %1").arg(server->errorString()));
        close();
        return;
    }

    portLabel->setText(tr("Server is running on port %1.").arg(server->serverPort()));
    setWindowTitle(tr("Chat Server"));
}

void Widget::clientConnect() {
    QTcpSocket *client = server->nextPendingConnection();
    // 서버에 연결 대기중인 client를 가져옴

    clients.push_back(client);

    connect(client, SIGNAL(disconnected()), SLOT(clientDisconnect()));
    connect(client, SIGNAL(readyRead()), SLOT(clientResponse()));
    label->setText("new connection established!");

    // 입장 알림
    //broadcast(client->peerAddress().toString() + " entered chat");
}

void Widget::clientResponse() {
    // client가 보낸 무언가가 있으면 읽어서 처리

    QTcpSocket *client = (QTcpSocket *)sender();
    if (client->bytesAvailable() > BLOCK_SIZE)
        return;

    QByteArray bytearray = client->read(BLOCK_SIZE);
    Message msg = Message::fromByteArray(bytearray);

    switch (msg.code) {
    case Message::REQUEST_LOGIN:
        // 임시 -> 여기서 로그인 유효성 확인 필요

        // 로그인 성공
        if (msg.data["id"] == "aaa" && msg.data["password"] == "aaa") {
            client->write(Message::getAckMessage().toByteArray());
        }
        else {  // 로그인 실패
            client->write(Message::getNackMessage().toByteArray());
        }

        break;

    case Message::REQUEST_REGISTER:
        // msg["id"] 등으로 접근 가능
        // DB User 삽입

        break;

    case Message::MESSAGE:
        broadcastChat(msg);
        break;

    default:
        break;
    }

}

void Widget::broadcastChat(Message& msg) {

    QByteArray msgByte = msg.toByteArray();

    // 연결된 모든 클라이언트들(배열)에 전송
    for (const auto& client : clients) {
        client->write(msgByte);
    }

    // DB 삽입


    //label->setText(QString(msg.data[]));
}

void Widget::clientDisconnect() {
    QTcpSocket *client = (QTcpSocket *)sender();

    // 퇴장 알림
    broadcast(client->peerAddress().toString() + " left chat");

    client->deleteLater();
    clients.removeOne(client);  // 클라이언트 배열에서 삭제
}

//
void Widget::broadcast(QString msgString) {
    QByteArray byte = msgString.toUtf8();

    for (const auto& client : clients) {
        client->write(byte);
    }

    label->setText(msgString);
}

Widget::~Widget() {}
