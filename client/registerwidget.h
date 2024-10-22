#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTcpSocket;

class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);

private:
    QLineEdit* inputID;
    QLineEdit* inputPW;
    QLineEdit* inputName;
    QLineEdit* inputPhonenum;

    QPushButton* submitBtn;
    QPushButton* backBtn;

    QTcpSocket* serverSocket;

private slots:
    void submit();
    void receive();
    void backToLogin();

signals:
};

#endif // REGISTERWIDGET_H
