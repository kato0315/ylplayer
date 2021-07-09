#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    setUi();
}

Dialog::~Dialog()
{
    delete mainWidget; 
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
    titlePainter.drawRect(QRect(0,0,this->width(),this->height()/10));
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
}

//按键函数
void Dialog::sendMsgSlot()
{
    QString seturl = "play:";
    QString filepath = mainWidget->getCurrentDirPath()+"/"+mainWidget->getCheckedButton()->text();
    filepath.replace(default_path,"");
    qDebug() <<"filepaht:"<<filepath;
    QByteArray ba = (seturl+filepath).toUtf8();
    server->sendMessage(ba.data(),strlen(ba.data()));

}

void Dialog::onClickedBtnPlay()
{
    qDebug() << "test BtnPlay" <<endl;

    if(mainWidget->getCheckedButton() == 0){
        return;
    }
    /*
    p.show();
    QTimer::singleShot(2000,this,SLOT(sendMsgSlot()));
*/
    if(server->socketFlag == true){
        p.show();
        QTimer::singleShot(2000,this,SLOT(sendMsgSlot()));

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("未连接本地播放器，无法播放！");
        msgBox.exec();
    }
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
    if(this->height() == 1080)
        btnFont.setPointSize(14);
    else if(this->height() == 900)
        btnFont.setPointSize(12);
    else
        btnFont.setPointSize(10);

    btnPlay->setText("播放视频");
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
    btnQuit->move(this->width()-30-(titleLb->height()/2 -15),titleLb->height()/2 -15);
    btnQuit->resize(30,30);
    connect(btnQuit,&QPushButton::clicked,this,&Dialog::close);

}

void Dialog::setFileWidget()
{
    mainWidget = new fileWidget(this->height()/9*7,this->height()/9*7,this);
    mainWidget->move((this->width()/2 - this->height()/9*7/2),(this->height()/2 - this->height()/9*7/2));
}

void Dialog::setPlayWidget()
{
    p.setGeometry(0,0,this->width(),this->height());
    p.setServer(this->server);
}

void Dialog::setUi()
{   
    server = new Server(this);

    QDesktopWidget *desktopWidget = QApplication::desktop();
    this->setGeometry(desktopWidget->screenGeometry());


    this->setWindowFlags(//置顶Qt::WindowStaysOnTopHint|
                         Qt::FramelessWindowHint);//去掉边框

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_QuitOnClose,true);

    //主要参照物
    setFileWidget();

    setupShadowBox();
    setBtn();
    setPlayWidget();

}

bool Dialog::showDialog()
{
    if(QDir(default_path).exists()){
        this->showFullScreen();
        return true;
    }
    else{
        QMessageBox msgbox;
        msgbox.setText("未能找到共享文件夹，请在虚拟机登陆方式模式一下使用该播放器。");
        msgbox.exec();
        return false;
    }

}
