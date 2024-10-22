#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class QTcpSocket;

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);

private:
    QLineEdit* inputID;
    QLineEdit* inputPW;
    QPushButton* submitBtn;
    QPushButton* registerBtn;
    QTcpSocket *serverSocket;

private slots:
    void submit();
    void receive();
    void registerAct();

signals:
};

#endif // LOGINWIDGET_H
