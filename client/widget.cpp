#include "widget.h"

#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#define BLOCK_SIZE      1024

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    // 서버 연결 소켓 생성
    serverSocket = new QTcpSocket(this);

    // 서버 주소 입력줄
    QLineEdit* serverAddress = new QLineEdit(this);
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
    QLineEdit* serverPort = new QLineEdit(this);
    serverPort->setInputMask("00000;_");
    serverPort->setPlaceholderText("Server Port Number");
    connect(serverPort, &QLineEdit::returnPressed, [=] {
        serverSocket->connectToHost(serverAddress->text(), serverPort->text().toInt());
    });

    // 서버 연결 버튼
    QPushButton* connectBtn = new QPushButton("connect", this);
    connect(connectBtn, &QPushButton::clicked, [=]{
        serverSocket->connectToHost(serverAddress->text(), serverPort->text().toInt());
    });

    // 서버 :horizon 가로 레이아웃
    QHBoxLayout* serverLayout = new QHBoxLayout;
    serverLayout->addStretch(1);
    serverLayout->addWidget(serverAddress);
    serverLayout->addWidget(serverPort);
    serverLayout->addWidget(connectBtn);

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
    mainLayout->addLayout(serverLayout);
    mainLayout->addWidget(message);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    // 서버 소켓 설정 - signal, slot
    connect(serverSocket, &QAbstractSocket::errorOccurred, [=] {
        qDebug() << serverSocket->errorString();
    });

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
