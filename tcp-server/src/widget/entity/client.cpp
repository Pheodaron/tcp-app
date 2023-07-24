#include "client.h"

Client::Client(QHostAddress ip, int port, QString lastMessage)
    : m_ip(ip), m_port(port), m_lastMessage(lastMessage) {}

Client::Client(QTcpSocket *socket) : m_ip(socket->peerAddress()), m_port(socket->peerPort()) {}
