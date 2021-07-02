#include "playwidget.h"
//#include "ui_playwidget.h"

playWidget::playWidget(QWidget *parent) :
    QWidget(parent)
{
    quit = false;
   // volumeControl = new SystemVolume;
    setWidgetUi();
    //ui->setupUi(this);
    //currentVolume = volumeControl->GetVolume();

}

playWidget::~playWidget()
{

}

void playWidget::keyPressEvent(QKeyEvent *event)
{

    switch(event->key())
    {
    case Qt::Key_Space:
        strcpy(cmd,button_commands[1].strCommand);
        server->sendMessage(cmd,strlen(cmd));
        qDebug() << "pause function" << endl;
        break;
    case Qt::Key_Escape:
        strcpy(cmd,button_commands[2].strCommand);
        server->sendMessage(cmd,strlen(cmd));
        quit = true;
        this->close();
        break;
    case Qt::Key_Right:
        strcpy(cmd,button_commands[3].strCommand);
        server->sendMessage(cmd,strlen(cmd));
        qDebug() << "back 10 seconds" <<endl;
        break;
    case Qt::Key_Left:
        strcpy(cmd,button_commands[4].strCommand);
        server->sendMessage(cmd,strlen(cmd));
        qDebug() << "forward 30 seconds" <<endl;
        break;
    case Qt::Key_Up:
        strcpy(cmd,button_commands[5].strCommand);
        server->sendMessage(cmd,strlen(cmd));
        qDebug() << "volume increase" <<endl;
        break;
    case Qt::Key_Down:
        strcpy(cmd,button_commands[6].strCommand);
        server->sendMessage(cmd,strlen(cmd));
        qDebug() << "volume decrease" <<endl;
        break;
    default:
        break;
        //playWidget::keyPressEvent(event);

    }

}

void playWidget::closeEvent(QCloseEvent *event)
{
    if(quit ==true){
        event->accept();
        quit = false;
    }
    else
        event->ignore();

    qDebug() << "close test" <<endl;

}
void playWidget::setWidgetUi()
{

    this->setWindowFlags(Qt::WindowStaysOnTopHint|//置顶
                         Qt::X11BypassWindowManagerHint|//兼容x11环境
                         Qt::FramelessWindowHint);//去掉边框
    this->setStyleSheet("#Dialog{background-color:#000000}");
}


void playWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/keyboard_guide.jpg"),QRect());
}

void playWidget::setServer(Server *s)
{
    server = s;
}
