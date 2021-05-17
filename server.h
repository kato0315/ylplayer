#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QString>

#define COMMAND_SET_SOURCE      0x101   //* set url of media file.
#define COMMAND_PLAY            0x102   //* start playback.
#define COMMAND_PAUSE           0x103   //* pause the playback.
#define COMMAND_STOP            0x104   //* stop the playback.
#define COMMAND_SEEKTO          0x105   //* seek to posion, in unit of second.
#define COMMAND_SHOW_MEDIAINFO  0x106   //* show media information.
#define COMMAND_SHOW_DURATION   0x107   //* show media duration, in unit of second.
#define COMMAND_SHOW_POSITION   0x108   //* show current play position, in unit of second.

typedef struct Command
{
    const char* strCommand;
    int nCommandId;
}Command;

const Command commands[] =
{
    {"set url:",COMMAND_SET_SOURCE},
    {"play",COMMAND_PLAY},
    {"pause",COMMAND_PAUSE},
    {"stop",COMMAND_STOP},
    {"seek to",COMMAND_SEEKTO},
    {"show media info",COMMAND_SHOW_MEDIAINFO},
    {"show duration",COMMAND_SHOW_DURATION},
    {"show position",COMMAND_SHOW_POSITION},
    {"NULL",0}
};


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
