#include "playwidget.h"
//#include "ui_playwidget.h"

playWidget::playWidget(QWidget *parent) :
    QWidget(parent)
{
    quit = false;
    volumeControl = new SystemVolume;
    setWidgetUi();
    //ui->setupUi(this);
    currentVolume = volumeControl->GetVolume();

}

playWidget::~playWidget()
{
    volumeControl->Close();
    //delete ui;
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
        qDebug() << "forward 10 seconds" <<endl;
        break;
    case Qt::Key_Up:
        qDebug() << "increase volume";
        if(currentVolume+5 <= 100){
            currentVolume += 5;
            volumeControl->SetVolume(currentVolume);
            qDebug() << currentVolume;
        }
        break;
    case Qt::Key_Down:
        qDebug() << "decrease volume";
        if(currentVolume-5 >= 0){
            currentVolume -= 5;
            volumeControl->SetVolume(currentVolume);
            qDebug() << currentVolume;
        }
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

    //this->setFixedSize(1920,1080);
    this->setWindowFlags(Qt::WindowStaysOnTopHint|//置顶
                         Qt::X11BypassWindowManagerHint|//兼容x11环境
                         Qt::FramelessWindowHint);//去掉边框
//阴影效果
    //this->setWindowOpacity(0.7);//透明度
    this->setStyleSheet("#Dialog{background-color:#000000}");
    //单独使用的话可以点击非控件区域控制背景后
    //this->setAttribute(Qt::WA_TranslucentBackground);



}


void playWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/keyboard_guide.jpg"),QRect());
    //painter.drawLine(QPoint(0,0),QPoint(100,100));
}
