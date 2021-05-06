#include "filewidget.h"
#include "ui_filewidget.h"

fileWidget::fileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileWidget)
{
    uiInit();
    ui->setupUi(this);
}

fileWidget::~fileWidget()
{
    delete ui;
}

void fileWidget::paintEvent(QPaintEvent *)
{
    QPainter mainPainter(this);
    QPen pen1(QColor(38,43,47));
    QBrush brush(QColor(38,43,47));
    mainPainter.setPen(pen1);
    mainPainter.setBrush(brush);
    mainPainter.drawRect(QRect(0,0,800,800));

}

void fileWidget::setBackground()
{
    this->setFixedSize(800,800);
    QPoint globalpos = this->mapToGlobal(QPoint(0,0));//取父窗口的坐标
    this->move(globalpos.x()+560,globalpos.y()+160);

    QFont titleFont;
    titleFont.setPointSize(20);

    fileTitle = new QLabel(this);
    fileTitle->setFont(titleFont);
    fileTitle->setText("所有视频");
    fileTitle->move(50,50);
    fileTitle->resize(300,30);
    fileTitle->setStyleSheet("color:#ffffff");

    dirTitle = new QLabel(this);
    dirTitle->setFont(titleFont);
    dirTitle->setText("文件夹");
    dirTitle->move(50,390);
    dirTitle->resize(300,30);
    dirTitle->setStyleSheet("color:#ffffff");
}

void fileWidget::setFileArea()
{
    fileSa = new QScrollArea(this);
    fileSa->setStyleSheet("background-color:#32363b;");
    fileSa->setGeometry(50,80,700,300);
    fileSa->verticalScrollBar();//垂直拖动条
    fileSa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    videoFile = new QWidget(fileSa);
    videoFile->setGeometry(0,0,700,300);


    fileButtonGroup = new QButtonGroup(this);
    fileButtonGroup->setExclusive(true);//设置互斥，实现单选效果
}

void fileWidget::setDirArea()
{
    dirSa = new QScrollArea(this);
    dirSa->setStyleSheet("background-color:#32363b;");
    dirSa->setGeometry(50,420,700,300);
    dirSa->verticalScrollBar();//垂直拖动条
    dirSa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    videoDir = new QWidget(dirSa);
    videoDir->setGeometry(0,0,700,300);


    dirButtonGroup = new QButtonGroup(this);
    dirButtonGroup->setExclusive(true);
}

void fileWidget::setPathArea()
{
    currentDir = new QDir();
    QFont dirFont;
    dirFont.setPointSize(18);
    videoPathLb = new QLabel(this);
    videoPathLb->setFont(dirFont);
    videoPathLb->move(50,730);
    videoPathLb->resize(700,50);
    videoPathLb->setStyleSheet("background-color:#212326;color:#ffffff;");

}

QAbstractButton* fileWidget::getCheckedButton()
{
    return fileButtonGroup->checkedButton();
}

void fileWidget::deleteDirButton()
{
    QToolButton* tempbutton;

    QFileInfoList dirList = currentDir->entryInfoList(QDir::Filter::Dirs | QDir::NoDotAndDotDot,QDir::SortFlag::Name);



    for(int i =0;i<dirList.size();i++){
        tempbutton = (QToolButton*)dirButtonGroup->button(i);

        delete tempbutton;
        qDebug() << "delete " << i <<" button"<<endl;
    }
}

void fileWidget::changeCurrentDir(QString dirString)
{
    //先判定原来是否有设置按钮，如果有按钮则把按钮对象释放
    if(dirButtonGroup->button(0) != NULL){
        deleteDirButton();

    }
    //修改路径
    currentDir->setPath(dirString);
    videoPathLb->setText(currentDir->path());
    //创建新路径中的文件按钮
    changeDirButton();
}

void fileWidget::test01()
{
   deleteDirButton();

}


void fileWidget::onDoubleClickedButton()
{
    QString changePath = currentDir->path() +"/" +((QToolButton*)sender())->text();
    qDebug() << changePath<<endl;
    changeCurrentDir(changePath);


}
/*
void fileWidget::changeCurrentDir()
{
    qDebug() << "change dir"<<endl;
    qDebug() << ((QToolButton*)sender())->text()<<endl;
    QString changePath = currentDir->path() +"/" +((QToolButton*)sender())->text();
    qDebug() << changePath<<endl;
    setCurrentDir(changePath);
}
*/

void fileWidget::changeDirButton()
{
    QFileIconProvider icon_provider;

    QFileInfoList dirList = currentDir->entryInfoList(QDir::Filter::Dirs | QDir::NoDotAndDotDot,QDir::SortFlag::Name);
    qDebug() << "file number:" << dirList.size();

    if(dirList.size() > 10){
        //文件布局位置超出原界面则扩展原界面大小
        videoDir->resize(700,150*(dirList.size()/5));
    }

    for(int i =0;i < dirList.size();i++){
        qDebug() << dirList.at(i).fileName();
        dirButton = new toolbutton(videoDir);

        dirButton->resize(90,100);
        dirButton->setIcon(icon_provider.icon(dirList.at(i)));
        dirButton->setIconSize(QSize(90,90));
        dirButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        dirButton->setCheckable(true);
        dirButton->setStyleSheet("QToolButton{"
                            "background-color:#32363b;"
                            "color:#ffffff;"
                            "border-color:#76B900;"
                            "}"

                            "QToolButton:checked{"
                            "background-color:#76B900"
                            "}");

        dirButton->setText(dirList.at(i).fileName());
        dirButtonGroup->addButton(dirButton);
        dirButtonGroup->setId(dirButton,i);
        dirButton->move(15+(i%5)*135,15+((i/5)*150));

        qDebug() << dirButtonGroup->button(i)->text()<<endl;
        connect(dirButton,SIGNAL(doubleClicked()),this,SLOT(onDoubleClickedButton()));
        dirButton->show();
    }

}





    /*
    QFileIconProvider icon_provider;

    QFileInfoList filelist = currentDir->entryInfoList(QDir::Filter::Files,QDir::SortFlag::Name);
    qDebug() << "file number:" << filelist.size();

    if(filelist.size() > 10){
        //文件布局位置超出原界面则扩展原界面大小
        videoFile->resize(700,150*(filelist.size()/5));
    }

    for(int i =0;i<filelist.size();i++){

        fileButton = new QToolButton(videoFile);

        fileButton->resize(90,100);
        fileButton->setIcon(icon_provider.icon(filelist.at(i)));
        fileButton->setIconSize(QSize(90,90));
        fileButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        fileButton->setCheckable(true);
        fileButton->setStyleSheet("QToolButton{"
                            "background-color:#32363b;"
                            "color:#ffffff;"
                            "border-color:#76B900;"
                            "}"
                            "QToolButton:hover{"
                            "border-color:#ffffff"
                            "}"
                            "QToolButton:checked{"
                            "background-color:#76B900"
                            "}");

        fileButton->setText(filelist.at(i).fileName());
        fileButtonGroup->addButton(fileButton);
        fileButton->move(15+(i%5)*135,15+((i/5)*150));

    }
*/



void fileWidget::uiInit()
{
    setBackground();
    setFileArea();
    setDirArea();
    setPathArea();

    changeCurrentDir(default_path);
}






