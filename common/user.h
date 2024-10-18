#ifndef USER_H
#define USER_H

#include <QObject>
#include <QTcpServer>

class User : public QObject
{
    Q_OBJECT

public:
    explicit User(QObject *parent = nullptr);
    QString getId();
    QString getName();

private:
    QString id;
    QString name;
    QString phone;
    QTcpSocket* socket;

signals:

};

#endif // USER_H
