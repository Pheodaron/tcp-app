#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QHostAddress>
#include <QTcpSocket>

// не используется будет удалено
class Client
{
public:
    Client(QHostAddress ip, int port, QString lastMessage);
    Client(QTcpSocket *socket);
    Client() = default;

    QHostAddress m_ip;
    int m_port;
    QString m_lastMessage;
};

#endif // CLIENT_H
