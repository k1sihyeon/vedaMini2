#include "message.h"

Message::Message(QObject *parent/*, int code, QString msg, User user*/) : QObject{parent}
{
    // this->code = code;
    // this->msg = msg;
    // this->user = user;
}

QByteArray Message::makeBtye() {
    QByteArray bytearray;
    QDataStream stream(&bytearray, QIODevice::WriteOnly);

    // QDataStream으로 직렬화
    stream << this->code << this->msg << this->user.getId() << this->user.getName();

    return bytearray;
}
