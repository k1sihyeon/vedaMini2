#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

class Message;
class QTcpServer;
class QTcpSocket;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void clientConnect();
    void clientResponse();
    void clientDisconnect();

private:
    QTcpServer *server;
    QLabel *label;
    QVector<QTcpSocket *> clients;

    void broadcastChat(Message& msg);
    void broadcast(QString msgString);

};
#endif // WIDGET_H
