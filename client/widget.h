#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QTcpSocket>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void getData();
    void sendData();

private:
    QTextEdit *message;
    QLineEdit *inputLine;
    QTcpSocket *serverSocket;
};
#endif // WIDGET_H
