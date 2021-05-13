#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    listen(QHostAddress::Any,18888);
}


void Server::incomingConnection(qintptr handle)
{


    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(handle);
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));

}

void Server::receiveMessage()
{
    char buffer[1024];
    socket->read(buffer,socket->bytesAvailable());
    qDebug() << buffer;
}

void Server::sendMessage(char *data, int len)
{
    socket->write(data,len);

}
