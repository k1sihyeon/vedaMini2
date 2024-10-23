#include "registerwidget.h"
#include "loginwidget.h"
#include "connectwidget.h"

#include "../common/message.h"

#include <QtWidgets>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>

#define BLOCK_SIZE      1024

RegisterWidget::RegisterWidget(QWidget *parent) : QWidget{parent}
{
    serverSocket = ConnectWidget::getInstance()->getServerSocket();
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(receive()));

    inputID = new QLineEdit(this);
    inputID->setPlaceholderText(tr("Input ID"));

    inputPW = new QLineEdit(this);
    inputPW->setPlaceholderText(tr("Input Password"));

    inputName = new QLineEdit(this);
    inputName->setPlaceholderText(tr("Input Name"));

    inputPhonenum = new QLineEdit(this);
    inputPhonenum->setPlaceholderText(tr("Input Phone Number"));

    submitBtn = new QPushButton(tr("submit"), this);
    backBtn = new QPushButton(tr("back to Login"), this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(inputID);
    mainLayout->addWidget(inputPW);
    mainLayout->addWidget(inputName);
    mainLayout->addWidget(inputPhonenum);
    mainLayout->addWidget(submitBtn);
    mainLayout->addWidget(backBtn);

    connect(submitBtn, SIGNAL(clicked()), this, SLOT(submit()));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToLogin()));
}

void RegisterWidget::submit() {
    if (inputID->text().isEmpty() || inputPW->text().isEmpty() || inputName->text().isEmpty() || inputPhonenum->text().isEmpty()) {
        QMessageBox::warning(this, tr("Register Error"), tr("something is EMPTY!"));
        return;
    }

    QJsonObject data;
    data["id"] = inputID->text();
    data["password"] = inputPW->text();
    data["name"] = inputName->text();
    data["phone"] = inputPhonenum->text();

    Message msg(Message::REQUEST_REGISTER, data);
    serverSocket->write(msg.toByteArray());
}

void RegisterWidget::receive() {
    if (serverSocket->bytesAvailable() > BLOCK_SIZE)
        return;

    QByteArray bytearray = serverSocket->read(BLOCK_SIZE);
    Message msg = Message::fromByteArray(bytearray);

    // 회원가입 성공
    if (msg.code == Message::RESPONSE_ACK) {
        backToLogin();
        return;
    }
    // 회원가입 실패
    else if (msg.code == Message::RESPONSE_NACK) {
        inputID->clear();
        inputPW->clear();
        inputName->clear();
        inputPhonenum->clear();

        QMessageBox::warning(this, tr("Register Error"), tr("Check input"));
        return;
    }
}

void RegisterWidget::backToLogin() {
    LoginWidget* lw = new LoginWidget();
    lw->show();

    this->close();
    delete(this);
}
