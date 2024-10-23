#include "loginwidget.h"
#include "connectwidget.h"
#include "registerwidget.h"
#include "widget.h"

#include "../common/message.h"

#include <QMessageBox>
#include <QtGui>
#include <QtWidgets>
#include <QTcpSocket>

#define BLOCK_SIZE      1024

LoginWidget::LoginWidget(QWidget *parent) : QWidget{parent} {
    // 서버 소켓 받아오기
    serverSocket = ConnectWidget::getInstance()->getServerSocket();
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(receive()));

    // 입력줄, 버튼
    inputID = new QLineEdit(this);
    inputID->setPlaceholderText(tr("Input ID"));

    inputPW = new QLineEdit(this);
    inputPW->setPlaceholderText(tr("Input Password"));

    submitBtn = new QPushButton("Login", this);
    registerBtn = new QPushButton("Create Account", this);

    // connect(inputID, SIGNAL(returnPressed()), this, SLOT(submit()));
    connect(inputPW, SIGNAL(returnPressed()), this, SLOT(submit()));
    connect(submitBtn, SIGNAL(clicked()), this, SLOT(submit()));
    connect(registerBtn, SIGNAL(clicked()), this, SLOT(registerAct()));

    // 레이아웃 설정
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(inputID);
    mainLayout->addWidget(inputPW);
    mainLayout->addWidget(submitBtn);
    mainLayout->addWidget(registerBtn);
}

void LoginWidget::submit() {
    if (inputID->text().isEmpty() || inputPW->text().isEmpty()) {
        QMessageBox::warning(this, tr("Login Error"), tr("ID or PW is empty!"));
        return;
    }

    QJsonObject data;
    data["id"] = inputID->text();
    data["password"] = inputPW->text();

    Message msg(Message::REQUEST_LOGIN, data);
    serverSocket->write(msg.toByteArray());
}

void LoginWidget::receive() {
    if (serverSocket->bytesAvailable() > BLOCK_SIZE)
        return;

    QByteArray bytearray = serverSocket->read(BLOCK_SIZE);
    Message msg = Message::fromByteArray(bytearray);

    // 로그인 성공
    if (msg.code == Message::RESPONSE_ACK) {
        Widget* w = new Widget();
        w->show();

        this->close();
        delete(this);
        //this->close 는 객체 삭제가 아님
    }
    // 로그인 실패
    else if (msg.code == Message::RESPONSE_NACK) {
        inputID->clear();
        inputPW->clear();

        QMessageBox::warning(this, tr("Login Error"), tr("Check ID and PW!"));
        return;
    }
    // else if (msg.code == Message::MESSAGE) {
    //     qDebug() << "login widget takes message..";
    // }
    // else {
    //     qDebug() << "Unknown message code detected in login widget!";
    // }
}

void LoginWidget::registerAct() {
    RegisterWidget* rw = new RegisterWidget();
    rw->show();

    this->close();
    delete(this);
}
