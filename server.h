#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

#include <QDebug>

#define COMMAND_SET_SOURCE      "set url"   //* set url of media file.
#define COMMAND_PLAY            "play"   //* start playback.
#define COMMAND_PAUSE           "pause"   //* pause the playback.
#define COMMAND_STOP            "stop"   //* stop the playback.
#define COMMAND_SEEKTO          "seek to"   //* seek to posion, in unit of second.
#define COMMAND_SHOW_MEDIAINFO  "show media info"   //* show media information.
#define COMMAND_SHOW_DURATION   "show duration"   //* show media duration, in unit of second.
#define COMMAND_SHOW_POSITION   "show position"   //* show current play position, in unit of second.


class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void sendMessage(char* data,int len);

private slots:
    void incomingConnection(qintptr handle) override;
    void receiveMessage();

private:
    QTcpSocket *socket;

signals:

};

#endif // SERVER_H
