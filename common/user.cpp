#include "user.h"

User::User(QString id, QString name, QString phone, QTcpSocket* socket, QObject *parent)
    : QObject{parent}
{
    this->id = id;
    this->name = name;
    this->phone = phone;
    this->socket = socket;
}

QString User::getId() {
    return this->id;
}

QString User::getName() {
    return this->name;
}
