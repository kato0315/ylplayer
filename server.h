#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QString>

//#include <QDebug>

//自定义
#define COMMAND_PLAY_BUTTON     0x0001
#define COMMAND_PAUSE_BUTTON    0x0002
#define COMMAND_STOP_BUTTON     0x0003
#define COMMAND_FORWARD_BUTTON  0x0004
#define COMMAND_BACK_BUTTON     0x0005
#define COMMAND_VOLUME_INCREASE 0x0006
#define COMMAND_VOLUME_DECREASE 0x0007
#define COMMAND_PLAYHTTP_BUTTON 0x0011

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
    {"volumeincrease",COMMAND_VOLUME_INCREASE},
    {"volumedecrease",COMMAND_VOLUME_DECREASE},
    {"playhttp:",COMMAND_PLAYHTTP_BUTTON},
    {NULL,0}
};

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

public slots:
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
