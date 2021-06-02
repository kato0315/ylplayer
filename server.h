#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QString>


//xplayer定义
/*
#define COMMAND_SET_SOURCE      0x101   // set url of media file.
#define COMMAND_PLAY            0x102   // start playback.
#define COMMAND_PAUSE           0x103   // pause the playback.
#define COMMAND_STOP            0x104   // stop the playback.
#define COMMAND_SEEKTO          0x105   // seek to posion, in unit of second.
#define COMMAND_SHOW_MEDIAINFO  0x106   // show media information.
#define COMMAND_SHOW_DURATION   0x107   // show media duration, in unit of second.
#define COMMAND_SHOW_POSITION   0x108   // show current play position, in unit of second.

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
*/
//自定义
#define COMMAND_PLAY_BUTTON     0x0001
#define COMMAND_PAUSE_BUTTON    0x0002
#define COMMAND_STOP_BUTTON     0x0003
#define COMMAND_FORWARD_BUTTON  0x0004
#define COMMAND_BACK_BUTTON     0x0005

typedef struct Button_Command{
    const char* strCommand;
    int commandId;
}Button_Command;

const Button_Command button_commands[]=
{
    {"play:",COMMAND_PLAY_BUTTON},
    {"pause",COMMAND_PAUSE_BUTTON},
    {"stop",COMMAND_STOP_BUTTON},
    {"forward",COMMAND_FORWARD_BUTTON},
    {"back",COMMAND_BACK_BUTTON},
    {NULL,0}
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
public:
    bool socketFlag;
signals:

};

#endif // SERVER_H
