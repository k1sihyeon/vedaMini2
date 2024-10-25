#ifndef MESSAGE_H
#define MESSAGE_H

#include <QIODevice>
#include <QJsonObject>

class QByteArray;
class QJsonObject;

class Message
{
public:
    Message();
    Message(int code, const QJsonObject& data);
    Message(int code, const QJsonObject& data, const QByteArray& fileData);

    QByteArray toByteArray();
    static Message fromByteArray(const QByteArray& byteArray);
    static Message getAckMessage();
    static Message getNackMessage();

    enum CODE {
        REQUEST_LOGIN,
        REQUEST_REGISTER,
        RESPONSE_ACK,
        RESPONSE_NACK,
        RESPONSE_LOGIN,
        RESPONSE_REGISTER,
        REQUEST_FILE_SHARE,
        RESPONSE_FILE_SHARE,
        MESSAGE,
    };

    int code;
    QJsonObject data;
    QByteArray  fileData;

};

#endif // MESSAGE_H
