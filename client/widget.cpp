#include "widget.h"
#include "connectwidget.h"

#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#define BLOCK_SIZE      1024

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    serverSocket = ConnectWidget::getInstance()->getServerSocket();

    // 메시지 표시 text edit
    message = new QTextEdit(this);
    message->setReadOnly(true);

    // 메시지 입력 줄
    inputLine = new QLineEdit(this);
    connect(inputLine, SIGNAL(returnPressed()), SLOT(sendData()));

    QPushButton* sendBtn = new QPushButton("Send", this);
    connect(sendBtn, SIGNAL(clicked()), SLOT(sendData()));

    // 입력 레이아웃 : horizon 가로
    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(inputLine);
    inputLayout->addWidget(sendBtn);

    // 연결 종료 버튼
    QPushButton* quitBtn = new QPushButton("Quit", this);
    connect(quitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));

    // 버튼 레이아웃 :horizon 가로
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(quitBtn);

    // 메인 vertical 세로 레이아웃
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    //mainLayout->addLayout(serverLayout);
    mainLayout->addWidget(message);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(serverSocket, SIGNAL(readyRead()), SLOT(getData()));

    setWindowTitle(tr("Chat Client"));
}

Widget::~Widget() {
    serverSocket->close();
}

void Widget::getData() {
    QTcpSocket *serverSocket = dynamic_cast<QTcpSocket *>(sender());
    if (serverSocket->bytesAvailable() > BLOCK_SIZE)
        return;

    QByteArray bytearray = serverSocket->read(BLOCK_SIZE);
    message->append(QString(bytearray));
}

void Widget::sendData() {
    QString str = inputLine->text();
    if (str.length()) {
        QByteArray bytearray = str.toUtf8();
        serverSocket->write(bytearray);
        inputLine->clear();
    }
}
