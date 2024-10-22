#include "message.h"

#include <QByteArray>
#include <QDataStream>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

Message::Message() {

}

Message::Message(int code, const QJsonObject& data) {
    this->code = code;
    this->data = data;
}

QByteArray Message::toByteArray() {
    QByteArray bytearray;
    QDataStream stream(&bytearray, QIODevice::WriteOnly);
    QJsonDocument jsonDoc(this->data);

    stream <<this->code << jsonDoc.toJson(QJsonDocument::Compact);

    return bytearray;
}

Message Message::fromByteArray(const QByteArray& byteArray) {
    QDataStream stream(byteArray);

    int code;
    QByteArray jsonByte;

    stream >> code >> jsonByte;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByte);
    QJsonObject data = jsonDoc.object();

    return Message(code, data);
}

Message Message::getAckMessage() {
    QJsonObject dummy;
    Message ackMsg(RESPONSE_ACK, dummy);

    return ackMsg;
}

Message Message::getNackMessage() {
    QJsonObject dummy;
    Message nackMsg(RESPONSE_NACK, dummy);

    return nackMsg;
}
