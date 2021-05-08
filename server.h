#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

#include <QDebug>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private slots:
    void incomingConnection(qintptr handle) override;
    void receiveMessage();
private:
    QTcpSocket *socket;

signals:

};

#endif // SERVER_H
