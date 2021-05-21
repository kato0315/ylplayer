#include "filewidget.h"
#include "ui_filewidget.h"

fileWidget::fileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileWidget)
{

    uiInit();
    ui->setupUi(this);
}

fileWidget::fileWidget(int width,int height,QWidget *parent):
    QWidget(parent),
    ui(new Ui::fileWidget)
{
    this->setFixedSize(width,height);


    uiInit();
    ui->setupUi(this);
}

fileWidget::~fileWidget()
{
    delete ui;
}

QString fileWidget::getCurrentDirPath()
{
    return currentDir->path();
}

//槽函数
void fileWidget::onDoubleClickedButton(QString text)
{
    //qDebug() << text <<endl;
    //获取更换的路径
   // QString changePath = currentDir->path() +"/" +((QToolButton*)sender())->text();
    changeCurrentDir(text);


}

void fileWidget::onClickedBtnAdd()
{
    qDebug() << "button add" <<endl;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("添加视频文件"),
                                                    "E:");
    if(fileName != NULL){
        QFile chosenFile(fileName);
        QFileInfo chosenFileInfo(chosenFile);

        if(chosenFileInfo.path() != currentDir->path())
        {
            QString copiedFileName =currentDir->path() + "/" + chosenFileInfo.fileName();
            chosenFile.copy(copiedFileName);
            deleteFileButton();
            createFileButton();
        }
        else
            //qDebug() << "same path"<<endl;
            return;

    }
    else
        qDebug() << "quit" <<endl;
}

void fileWidget::onClickedBtnDelete()
{
    qDebug() << "button delete" <<endl;
    if(getCheckedButton()!=NULL)
    {
        qDebug() <<getCheckedButton()->text()<<endl;
        QString deleteFileName = currentDir->path() + "/" +getCheckedButton()->text();
        QFile deleteFile(deleteFileName);

        deleteFileButton();

        if(deleteFile.remove())
        {
            qDebug() << "remove success";
            createFileButton();
        }
        else
        {
            qDebug() << "remove fail";
            createFileButton();
            return;
        }

    }
    else
        qDebug() << "no checked button"<<endl;

}

void fileWidget::onClickedBtnBack()
{

    if(currentDir->path() != default_path){

        changeCurrentDir();
    }
    else
        qDebug() << "no back" <<endl;
}

//设置背景颜色
void fileWidget::paintEvent(QPaintEvent *)
{
    QPainter mainPainter(this);
    QPen pen1(QColor(38,43,47));
    QBrush brush(QColor(38,43,47));
    mainPainter.setPen(pen1);
    mainPainter.setBrush(brush);
    mainPainter.drawRect(QRect(0,0,this->width(),this->height()));

}

//设置基本布局
void fileWidget::setBackground()
{
    //this->setFixedSize(800,800);
    QPoint globalpos = this->mapToGlobal(QPoint(0,0));//取父窗口的坐标
    this->move(globalpos.x()+560,globalpos.y()+160);

    QFont titleFont;
    titleFont.setPointSize(20);

    fileTitle = new QLabel(this);
    fileTitle->setFont(titleFont);
    fileTitle->setText("所有视频");
    fileTitle->move(x_position,50);
    fileTitle->resize(sa_width,30);
    fileTitle->setStyleSheet("color:#ffffff");

    dirTitle = new QLabel(this);
    dirTitle->setFont(titleFont);
    dirTitle->setText("文件夹");
    dirTitle->move(x_position,390);
    dirTitle->resize(sa_width,30);
    dirTitle->setStyleSheet("color:#ffffff");
}

//设置文件显示框
void fileWidget::setFileArea()
{

    fileSa = new QScrollArea(this);
    fileSa->setStyleSheet("background-color:#32363b;");
    fileSa->setFixedSize(sa_width,sa_height);
    fileSa->move(x_position,80);
    //fileSa->setGeometry(50,80,this->width()/7*6,this->width()/7*6/5*2);
    fileSa->verticalScrollBar();//垂直拖动条
    fileSa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    videoFile = new QWidget();
   // videoFile->setGeometry(0,0,700,600);
    fileSa->setWidget(videoFile);

    videoFile->setGeometry(0,0,700,300);
    fileButtonGroup = new QButtonGroup(this);
    fileButtonGroup->setExclusive(true);//设置互斥，实现单选效果
}

//设置目录显示框
void fileWidget::setDirArea()
{
    dirSa = new QScrollArea(this);
    dirSa->setStyleSheet("background-color:#32363b;");
    dirSa->setFixedSize(sa_width,sa_height);
    dirSa->move(x_position,420);
    //dirSa->setGeometry(50,420,700,300);
    dirSa->verticalScrollBar();//垂直拖动条
    dirSa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    videoDir = new QWidget();
    dirSa->setWidget(videoDir);
    videoDir->setGeometry(0,0,700,300);


    dirButtonGroup = new QButtonGroup(this);
    dirButtonGroup->setExclusive(true);
}

//设置路径显示框
void fileWidget::setPathArea()
{
    currentDir = new QDir();
    QFont dirFont;
    dirFont.setPointSize(18);
    videoPathLb = new QLabel(this);
    videoPathLb->setFont(dirFont);
    videoPathLb->move(x_position,730);
    videoPathLb->resize(sa_width,50);
    videoPathLb->setStyleSheet("background-color:#212326;color:#ffffff;");

}

//返回选中文件的按钮
QAbstractButton* fileWidget::getCheckedButton()
{
    return fileButtonGroup->checkedButton();
}

//更换目录时释放原有的按钮
void fileWidget::deleteDirButton()
{
    QToolButton* tempbutton;

    QFileInfoList dirList = currentDir->entryInfoList(QDir::Filter::Dirs | QDir::NoDotAndDotDot,QDir::SortFlag::Name);
    for(int i =0;i<dirList.size();i++){
        tempbutton = (QToolButton*)dirButtonGroup->button(i);
        delete tempbutton; 
    }
}


void fileWidget::deleteFileButton()
{
    QToolButton* tempbutton;

    QFileInfoList dirList = currentDir->entryInfoList(QDir::Filter::Files,QDir::SortFlag::Name);
    qDebug() << currentDir->path();
    qDebug() << "delete file number:" << dirList.size();
    for(int i =0;i<dirList.size();i++){
        tempbutton = (QToolButton*)fileButtonGroup->button(i);
        qDebug() <<"delete button"<<endl;
        delete tempbutton;
    }
}

//创建按钮
void fileWidget::createDirButton()
{
    QFileIconProvider icon_provider;
    QFileInfoList dirList = currentDir->entryInfoList(QDir::Filter::Dirs | QDir::NoDotAndDotDot,QDir::SortFlag::Name);

    if(dirList.size() > 10){
        //文件布局位置超出原界面则扩展原界面大小
        videoDir->resize(700,150*(dirList.size()/5));
    }
    else
        videoDir->resize(700,300);

    for(int i =0;i < dirList.size();i++){
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

        connect(dirButton,SIGNAL(doubleClicked(QString)),this,SLOT(onDoubleClickedButton(QString)));
        dirButton->show();
    }

}

void fileWidget::createFileButton()
{

    QFileIconProvider icon_provider;

    QFileInfoList filelist = currentDir->entryInfoList(QDir::Filter::Files,QDir::SortFlag::Name);
    qDebug() << "file number:" << filelist.size();

    if(filelist.size() > 10){
        //文件布局位置超出原界面则扩展原界面大小
        videoFile->resize(700,150*(filelist.size()/5));
    }
    else
        videoFile->resize(700,300);

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
        fileButtonGroup->setId(fileButton,i);
        fileButton->move(15+(i%5)*135,15+((i/5)*150));
        fileButton->show();
    }

}

//更换目录
void fileWidget::changeCurrentDir()
{
    //先判定原来是否有设置按钮，如果有按钮则把按钮对象释放
    if(dirButtonGroup->button(0) != NULL | fileButtonGroup->button(0) != NULL){
        deleteDirButton();
        deleteFileButton();
    }
    //修改路径
    currentDir->cdUp();
    videoPathLb->setText(currentDir->path());
    //创建新路径中的文件按钮
    createDirButton();
    createFileButton();

}

void fileWidget::changeCurrentDir(QString dirString)
{
    //先判定原来是否有设置按钮，如果有按钮则把按钮对象释放
    if(dirButtonGroup->button(0) != NULL | fileButtonGroup->button(0) != NULL){
        deleteDirButton();
        deleteFileButton();
    }
    //修改路径
    currentDir->cd(dirString);
    videoPathLb->setText(currentDir->path());
    //创建新路径中的文件按钮
    createDirButton();
    createFileButton();
}

void fileWidget::uiInit()
{
    sa_width = this->width()/7*6;
    sa_height = this->width()/7*6/5*2;
    x_position = (this->width()-sa_width)/2;
    setFileArea();
    setDirArea();
    setBackground();

    setPathArea();

    changeCurrentDir(default_path);
}






