#include "playwidget.h"
#include "ui_playwidget.h"

playWidget::playWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playWidget)
{
    setWidgetUi();
    //ui->setupUi(this);
}

playWidget::~playWidget()
{
    delete ui;
}

void playWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        this->close();
        break;
    case Qt::Key_Space:
        qDebug() << "pause function" << endl;
    case Qt::Key_Left:
        qDebug() << "back 10 seconds" <<endl;
    case Qt::Key_Right:
        qDebug() << "forward 10 seconds" <<endl;
        break;
    default:
        playWidget::keyPressEvent(event);

    }

}

void playWidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "close test" <<endl;
    event->accept();
}
void playWidget::setWidgetUi()
{

    this->setFixedSize(1920,1080);
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
    painter.drawLine(QPoint(0,0),QPoint(100,100));
}
