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

Message::Message(int code, const QJsonObject& data, const QByteArray& fileData) {
    this->code = code;
    this->data = data;
    this->fileData = fileData;
}

QByteArray Message::toByteArray() {
    QByteArray bytearray;
    QDataStream stream(&bytearray, QIODevice::WriteOnly);
    QJsonDocument jsonDoc(this->data);

    stream <<this->code << jsonDoc.toJson(QJsonDocument::Compact);

    if (this->code == REQUEST_FILE_SHARE && !this->fileData.isNull()) {
        stream << this->fileData;
    }

    return bytearray;
}

Message Message::fromByteArray(const QByteArray& byteArray) {
    QDataStream stream(byteArray);

    int code;
    QByteArray jsonByte;

    stream >> code >> jsonByte;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByte);
    QJsonObject data = jsonDoc.object();

    if (code == REQUEST_FILE_SHARE) {
        QByteArray fileData;
        stream >> fileData;
        return Message(code, data, fileData);
    }

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
