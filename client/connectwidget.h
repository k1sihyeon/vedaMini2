#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>

class QTcpSocket;
class QLineEdit;

class ConnectWidget : public QWidget
{
    Q_OBJECT

private:
    inline static ConnectWidget* instance;
    inline static QTcpSocket *serverSocket;
    QLineEdit* serverAddress;
    QLineEdit* serverPort;

public:
    explicit ConnectWidget(QWidget *parent = nullptr);

    static ConnectWidget* getInstance() {
        // if (instance == nullptr) {
        //     instance = new ConnectWidget();
        // }

        return instance;
    }

    QTcpSocket* getServerSocket();

private slots:
    void connectAct();

signals:
};

#endif // CONNECTWIDGET_H
