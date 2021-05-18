#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    setUi();
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

//按键设置与屏蔽
void Dialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);

    }
}

//顶部黑框
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter titlePainter(this);
    QPen pen(QColor(0,0,0));
    QBrush brush(Qt::black);

    titlePainter.setPen(pen);
    titlePainter.setBrush(brush);
    titlePainter.drawRect(QRect(0,0,1920,100));

}

//阴影背景
void Dialog::setupShadowBox()
{
    QFont titleFont;
    titleFont.setPointSize(30);
    titleFont.setBold(true);
    titleFont.setFamily("KaiTi");
    titleLb = new QLabel(this);
    titleLb->setFont(titleFont);
    titleLb->setStyleSheet("QWidget{color:rgb(255,255,255);}");
    titleLb->setText("Yulong Player");
    titleLb->resize(this->width(),this->height()/10);
    titleLb->move(0,0);
    titleLb->setAlignment(Qt::AlignCenter);//居中

    shadowBox = new QWidget(this);
    shadowBox->setStyleSheet("QWidget{background-color:rgb(0,0,0,127);}");
    shadowBox->move(0,0);
    shadowBox->resize(this->width(),this->height());
    shadowBox->lower();

    videoLogo = new QWidget(this);
    videoLogo->setStyleSheet("QWidget{background-color:rgb(255,255,255);"
                             "border-image:url(:/videologo.png)"
                             "}");

    videoLogo->resize(this->width()/16*2,this->width()/16*2);
    videoLogo->move(mainWidget->x()-videoLogo->width()-20,mainWidget->y());
}

//按键函数
void Dialog::onClickedBtnPlay()
{
    qDebug() << "test BtnPlay" <<endl;
    QString seturl = "play:";

    QString filepath = mainWidget->getCurrentDirPath()+"/"+mainWidget->getCheckedButton()->text();
    QByteArray ba = (seturl+filepath).toLatin1();
    printf("%s",ba.data());

    server->sendMessage(ba.data(),strlen(ba.data()));

    //qDebug() << "get checked button" << mainWidget->getCheckedButton()->text();
    //QByteArray ba = mainWidget->getCheckedButton()->text().toLatin1();
    //server.sendMessage(ba.data(),strlen(ba.data()));
    p.show();

}



//按键设置
void Dialog::setBtn()
{
    btnPlay = new QPushButton(this);
    btnAdd = new QPushButton(this);
    btnDelete = new QPushButton(this);
    btnQuit = new QPushButton(this);
    btnBack = new QPushButton(this);

    int buttonWidth = this->width()/16*2;
    int buttonHeight = this->width()/16*2/3;
    int buttonX = mainWidget->x() + mainWidget->width() + 20;
    QFont btnFont;
    btnFont.setPointSize(14);


    btnPlay->setText("播放视频");
   // playFont.set
    btnPlay->setFont(btnFont);
    btnPlay->setStyleSheet("background-color:#76B900;"
                           "color:#ffffff;"
                           "border-color:#ffffff;");
    btnPlay->move(buttonX,mainWidget->y());
    btnPlay->resize(buttonWidth,buttonHeight);
    connect(btnPlay,&QPushButton::clicked,this,&Dialog::onClickedBtnPlay);

    btnAdd->setText("添加视频");
    btnAdd->setFont(btnFont);
    btnAdd->setStyleSheet("background-color:#32363b;color:#ffffff;border-color:#76B900;");
    btnAdd->move(buttonX,mainWidget->y()+(buttonHeight+20)*1);
    btnAdd->resize(buttonWidth,buttonHeight);
    connect(btnAdd,&QPushButton::clicked,mainWidget,&fileWidget::onClickedBtnAdd);

    btnDelete->setText("删除视频");
    btnDelete->setFont(btnFont);
    btnDelete->setStyleSheet("background-color:#32363b;color:#ffffff;border-color:#76B900;");
    btnDelete->move(buttonX,mainWidget->y()+(buttonHeight+20)*2);
    btnDelete->resize(buttonWidth,buttonHeight);
    connect(btnDelete,&QPushButton::clicked,mainWidget,&fileWidget::onClickedBtnDelete);

    btnBack->setText("后退");
    btnBack->setFont(btnFont);
    btnBack->setStyleSheet("background-color:#32363b;color:#ffffff;border-color:#76B900;");
    btnBack->move(buttonX,mainWidget->y()+(buttonHeight+20)*3);
    btnBack->resize(buttonWidth,buttonHeight);
    connect(btnBack,&QPushButton::clicked,mainWidget,&fileWidget::onClickedBtnBack);

    btnQuit->setStyleSheet("border-image:url(:/quit.png)");
    btnQuit->move(1870,30);
    btnQuit->resize(30,30);
   // btnQuit->setIcon(QIcon(":/quit.png"));
    connect(btnQuit,&QPushButton::clicked,this,&Dialog::close);


}

void Dialog::setMainWidget()
{
    mainWidget = new fileWidget(this);
    mainWidget->setGeometry((this->width()/2 - this->height()/9*7/2),(this->height()/2 - this->height()/9*7/2),this->height()/9*7,this->height()/9*7);

}

void Dialog::setUi()
{   
    server = new Server(this);
    p.server = this->server;

    QDesktopWidget *desktopWidget = QApplication::desktop();
    qDebug() << desktopWidget->screenGeometry();
    this->setGeometry(desktopWidget->screenGeometry());


    this->setWindowFlags(Qt::WindowStaysOnTopHint|//置顶
                         Qt::X11BypassWindowManagerHint|//兼容x11环境
                         Qt::FramelessWindowHint);//去掉边框

    this->setAttribute(Qt::WA_TranslucentBackground);

    //主要参照物
    setMainWidget();

    setupShadowBox();
    setBtn();


}
