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

//槽函数
//返回选中文件的按钮
QAbstractButton* fileWidget::getCheckedButton()
{
    return fileButtonGroup->checkedButton();
}

//获取目录路径
QString fileWidget::getCurrentDirPath()
{
    return currentDir->path();
}

//添加文件按钮实现复制功能
void fileWidget::onClickedBtnAdd()
{
    //qDebug() << "button add" <<endl;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("添加视频文件"),
                                                    "D:",
                                                    tr("Videos (*.avi *.mov *.flv *.MP4)"));//rm不支持
    if(fileName != NULL){
        QFile chosenFile(fileName);
        QFileInfo chosenFileInfo(chosenFile);

        if(chosenFileInfo.path() != currentDir->path())
        {
            QString copiedFileName =currentDir->path() + "/" + chosenFileInfo.fileName();
            //需要将/改为\\才能识别
            fileName.replace(QRegExp("\\/"),"\\");
            copiedFileName.replace(QRegExp("\\/"),"\\");

            wstring pFrom = fileName.toStdWString();
            wstring pTo = copiedFileName.toStdWString();
            //扩大wstring空间，保证字符串末端必定为\0
            pFrom.resize(pFrom.size()+2);
            pTo.resize(pTo.size()+2);
            fileOp.pFrom = pFrom.c_str();
            fileOp.pTo = pTo.c_str();
            int ret = 0;
            ret =SHFileOperation(&fileOp);
            //qDebug() <<"SHFileOp:"<< ret;
            if(ret == 0)
                refreshButtonInterface();
        }
        else
            //qDebug() << "same path"<<endl;
            return;

    }
    else{
    }
        //qDebug() << "quit" <<endl;
}

//删除按钮实现文件删除功能
void fileWidget::onClickedBtnDelete()
{
    //qDebug() << "button delete" <<endl;
    if(getCheckedButton()!=NULL)
    {
        //qDebug() <<getCheckedButton()->text()<<endl;
        QString deleteFileName = currentDir->path() + "/" +getCheckedButton()->text();
        QFile deleteFile(deleteFileName);

        if(deleteFile.remove())
        {
            //qDebug() << "remove success";
            refreshButtonInterface();
            refreshDirSize();
        }
        else
        {
            //qDebug() << "remove fail";
            return;
        }

    }
    else
    {
        //qDebug() << "no checked button"<<endl;
    }


}

//后退键实现切换上级目录功能
void fileWidget::onClickedBtnBack()
{

    if(currentDir->path() != default_path){
        changeCurrentDir();
    }
    else{
        //qDebug() << "no back" <<endl;
    }

}

//双击文件夹切换目录
void fileWidget::onDoubleClickedButton(QString text)
{
    changeCurrentDir(text);
    fileInfoLabel.close();
}

//鼠标指针指向文件时显示文件信息
void fileWidget::enteredFileButton(QString text)
{
  //  qDebug() << "enter file button:" <<text;
    QFileInfo chosenFile= currentDir->path()+"/"+text;
    QString sizeString = translateDirSize(chosenFile.size());
    QString displayText = "文件名："+chosenFile.fileName()+"\n" +"文件大小："+sizeString;
    fileInfoLabel.setText(displayText);
    fileInfoLabel.move(QCursor::pos().x()+10,QCursor::pos().y()+10);
    fileInfoLabel.show();
}

//鼠标指针指向文件夹时显示文件夹名
void fileWidget::enteredDirButton(QString text)
{
    fileInfoLabel.setText("文件夹名："+text);
    fileInfoLabel.move(QCursor::pos().x()+10,QCursor::pos().y()+10);
    fileInfoLabel.show();
}

//鼠标指针离开文件或文件夹时关闭显示的label
void fileWidget::leftButton()
{
    //qDebug() << "left button";
    fileInfoLabel.close();
}

//获取目录大小
quint64 fileWidget::getDirSize(const QString &path)
{
    QDir dir(path);
    quint64 size = 0;

    foreach(QFileInfo fileInfo,dir.entryInfoList(QDir::Files)){
        size += fileInfo.size();
    }

    foreach(QString subDir,dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)){
        size += getDirSize(path+QDir::separator()+subDir);
    }
    return size;
}

//以string形式返回dirsize
QString fileWidget::translateDirSize(quint64 size)
 {
     double translateSize;
     QString strSize;
     if(size >= 1024*1024*1024){
         translateSize = (double)size/(1024*1024*1024);
         strSize = QString::number(translateSize,'f',1)+"GB";
         return strSize;
     }
     else if(size >= 1024*1024){
         translateSize = (double)size/(1024*1024);
         strSize = QString::number(translateSize,'f',1)+"MB";
         return strSize;
     }
     else if(size >= 1024){
         translateSize = (double)size/1024;
         strSize = QString::number(translateSize,'f',1)+"KB";
         return strSize;
     }
     else{
         translateSize = size;
         strSize = QString::number(translateSize,'f',1)+"B";
         return strSize;
     }


 }

//刷新dirsize显示
void fileWidget::refreshDirSize()
{
    usedSpace = getDirSize(default_path);
    fileSpace->setText(translateDirSize(usedSpace));
}

//更换目录时释放原有的按钮
void fileWidget::deleteDirButton()
{
    foreach(QAbstractButton *tempbutton,dirButtonGroup->buttons()){
        delete tempbutton;
    }
}

void fileWidget::deleteFileButton()
{
    foreach(QAbstractButton *tempbutton,fileButtonGroup->buttons()){
        delete tempbutton;
    }
}

//创建文件夹按钮
void fileWidget::createDirButton()
{

    int button_size=sa_width/6;
    //qDebug() <<button_size;
    QFileInfoList dirList = currentDir->entryInfoList(QDir::Filter::Dirs | QDir::NoDotAndDotDot,QDir::SortFlag::Name);
    QIcon dirIcon = QIcon(":/fileIcon.png");


    if(dirList.size() > 10){
        //文件布局位置超出原界面则扩展原界面大小
        videoDir->resize(sa_width,(sa_height/2)*(dirList.size()/5 + 1));
    }
    else
        videoDir->resize(sa_width,sa_height);

    for(int i =0;i < dirList.size();i++){
        dirButton = new toolbutton(videoDir);

        dirButton->resize(button_size,button_size);
        dirButton->setIconSize(QSize(button_size,button_size/4*3));
        dirButton->setIcon(dirIcon);
        dirButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        dirButton->setCheckable(false);
        dirButton->setStyleSheet("QToolButton{"
                            "background-color:#32363b;"
                            "color:#ffffff;"
                            "border-color:#76B900;"
                            "}"

                                 );

        dirButton->setText(dirList.at(i).fileName());
        dirButtonGroup->addButton(dirButton);
        dirButtonGroup->setId(dirButton,i);
        dirButton->move(button_size/12+(i%5)*(button_size+button_size/6),button_size/12+(i/5)*(button_size+button_size/6));

        connect(dirButton,SIGNAL(doubleClicked(QString)),this,SLOT(onDoubleClickedButton(QString)));
        connect(dirButton,SIGNAL(enterButton(QString)),this,SLOT(enteredDirButton(QString)));
        connect(dirButton,SIGNAL(leaveButton()),this,SLOT(leftButton()));
        dirButton->show();
    }

}

//获取视频文件预览图
void fileWidget::getVideoPreview(QFileInfo file,QToolButton* fileButton)
{
    //QTime time;
    //time.start();

    AVFormatContext* fmt_ctx = nullptr;
    int ret;

    QByteArray ba = file.filePath().toUtf8();
    ret = avformat_open_input(&fmt_ctx, ba.data(), nullptr, nullptr);
    if (ret != 0) {
        //qDebug() << "avformat_open_input failed" << endl;

    }

    ret = avformat_find_stream_info(fmt_ctx,nullptr);
    if (ret != 0) {
        //qDebug() << "avformat_find_stream_info failed" << endl;

    }
    AVPacket* pkt = av_packet_alloc();
    AVFrame* temp_frame = av_frame_alloc();
    SwsContext* sws_ctx = nullptr;
    QImage preview;
    bool preview_done = false;
    int dstW = sa_width/6;
    int dstH = sa_width/8;

    for(unsigned int i = 0;(i < fmt_ctx->nb_streams) && (!preview_done);i++){
        //只处理视频信息
        if(fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            AVCodec* codec = avcodec_find_decoder(fmt_ctx->streams[i]->codecpar->codec_id);
            AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
            avcodec_parameters_to_context(codec_ctx,fmt_ctx->streams[i]->codecpar);
            avcodec_open2(codec_ctx,codec,nullptr);

            //读取帧数据
            av_seek_frame(fmt_ctx,-1,5*AV_TIME_BASE,AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
            while(av_read_frame(fmt_ctx,pkt) >= 0){
                av_frame_unref(temp_frame);
                //解码帧数据
                while( (ret = avcodec_receive_frame(codec_ctx,temp_frame)) ==AVERROR(EAGAIN)){
                    ret = avcodec_send_packet(codec_ctx,pkt);
                    if(ret < 0){
                        //qDebug()<<"failed to send packet to decoder.";
                        break;
                    }
                }

                if(ret < 0 && ret != AVERROR_EOF){
                    //qDebug()<<"failed to receive packet from decoder.";
                    continue;
                }

                //转换格式

               // qDebug() <<"icon width:" <<dstW <<" icon height:" << dstH;
                sws_ctx = sws_getContext(
                            temp_frame->width,
                            temp_frame->height,
                            static_cast<AVPixelFormat>(temp_frame->format),
                            dstW,
                            dstH,
                            static_cast<AVPixelFormat>(AV_PIX_FMT_RGBA),
                            SWS_FAST_BILINEAR,
                            nullptr,
                            nullptr,
                            nullptr
                            );
                int linesize[AV_NUM_DATA_POINTERS];
                linesize[0] = dstW*4;

                //生成图片
                preview = QImage(dstW,dstH,QImage::Format_RGBA8888);
                uint8_t* data = preview.bits();
                sws_scale(sws_ctx,
                          temp_frame->data,
                          temp_frame->linesize,
                          0,
                          temp_frame->height,
                          &data,
                          linesize);
                sws_freeContext(sws_ctx);
                avcodec_close(codec_ctx);
                avcodec_free_context(&codec_ctx);
                preview_done = true;
                break;
            }

        }

    }

    av_frame_free(&temp_frame);
    av_packet_free(&pkt);
    avformat_close_input(&fmt_ctx);

    if(preview_done){
        fileButton->setIcon(QIcon(QPixmap::fromImage(preview)));
        fileButton->setIconSize(QSize(dstW,dstH));
    }
    //qDebug() <<"preview test:" <<time.elapsed()/1000.0<<"s";
}

//创建文件按钮
void fileWidget::createFileButton()
{

    int button_size=sa_width/6;
    QDir tmpDir = *currentDir;
    QStringList filter;
    filter << "*.avi"<< "*.mov"<< "*.flv" << "*.MP4";   //过滤后缀名
    tmpDir.setNameFilters(filter);
    QFileInfoList filelist = tmpDir.entryInfoList(QDir::Filter::Files,QDir::SortFlag::Name);


    if(filelist.size() > 10){
        //文件布局位置超出原界面则扩展原界面大小
        //qDebug() << "resize";
        videoFile->resize(sa_width,(sa_height/2)*(filelist.size()/5 + 1));
    }
    else
        videoFile->resize(sa_width,sa_height);

    for(int i =0;i<filelist.size();i++){

        fileButton = new toolbutton(videoFile);

        fileButton->resize(button_size,button_size);
        getVideoPreview(filelist.at(i),fileButton);
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
        fileButton->move(button_size/12+(i%5)*(button_size+button_size/6),button_size/12+(i/5)*(button_size+button_size/6));

        connect(fileButton,SIGNAL(enterButton(QString)),this,SLOT(enteredFileButton(QString)));
        connect(fileButton,SIGNAL(leaveButton()),this,SLOT(leftButton()));
        fileButton->show();
    }
}

//文件数量变动时刷新按钮
 void fileWidget::refreshButtonInterface()
 {
     deleteFileButton();
     createFileButton();
     refreshDirSize();
 }

 //更换目录,回到上级目录
 void fileWidget::changeCurrentDir()
 {
     //先判定原来是否有设置按钮，如果有按钮则把按钮对象释放
     if( (dirButtonGroup->button(0) != NULL) | (fileButtonGroup->button(0) != NULL) ){
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

 //更换目录
 void fileWidget::changeCurrentDir(QString dirString)
 {
     //先判定原来是否有设置按钮，如果有按钮则把按钮对象释放
     if( (dirButtonGroup->button(0) != NULL) | (fileButtonGroup->button(0) != NULL) ){
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
    QFont titleFont;
    titleFont.setPointSize(interval_height-10);

    fileTitle = new QLabel(this);
    fileTitle->setFont(titleFont);
    fileTitle->setText("所有视频");
    fileTitle->move(x_position,interval_height);
    fileTitle->resize(sa_width/2,interval_height);
    fileTitle->setStyleSheet("color:#ffffff");

    fileSpace = new QLabel(this);
    fileSpace->setFont(titleFont);
    fileSpace->move(x_position+sa_width/2,interval_height);
    fileSpace->resize(sa_width/2,interval_height);
    fileSpace->setStyleSheet("color:#ffffff");
    fileSpace->setAlignment(Qt::AlignRight);


    fileSpace->setText(translateDirSize(usedSpace));

    dirTitle = new QLabel(this);
    dirTitle->setFont(titleFont);
    dirTitle->setText("文件夹");
    dirTitle->move(x_position,interval_height*3+sa_height);
    dirTitle->resize(sa_width,interval_height);
    dirTitle->setStyleSheet("color:#ffffff");
}

//设置目录显示框
void fileWidget::setDirArea()
{
    dirSa = new QScrollArea(this);
    dirSa->setStyleSheet("background-color:#32363b;");
    dirSa->setFixedSize(sa_width,sa_height);
    dirSa->move(x_position,interval_height*4+sa_height);
    //dirSa->setGeometry(50,420,700,300);
    dirSa->verticalScrollBar();//垂直拖动条
    dirSa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    videoDir = new QWidget();
    dirSa->setWidget(videoDir);
    videoDir->setGeometry(0,0,sa_width,sa_height);


    dirButtonGroup = new QButtonGroup(this);
    dirButtonGroup->setExclusive(true);
}

//设置文件显示框
void fileWidget::setFileArea()
{

    fileSa = new QScrollArea(this);
    fileSa->setStyleSheet("background-color:#32363b;");
    fileSa->setFixedSize(sa_width,sa_height);
    fileSa->move(x_position,interval_height*2);
    fileSa->verticalScrollBar();//垂直拖动条
    fileSa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    videoFile = new QWidget();
    fileSa->setWidget(videoFile);

    videoFile->setGeometry(0,0,sa_width,sa_height);
    fileButtonGroup = new QButtonGroup(this);
    fileButtonGroup->setExclusive(true);//设置互斥，实现单选效果
}

//设置路径显示框
void fileWidget::setPathArea()
{
    currentDir = new QDir();
    QFont dirFont;
    dirFont.setPointSize(interval_height-10);
    videoPathLb = new QLabel(this);
    videoPathLb->setFont(dirFont);
    videoPathLb->move(x_position,interval_height*5+sa_height*2);
    videoPathLb->resize(sa_width,interval_height*1.5);
    videoPathLb->setStyleSheet("background-color:#212326;color:#ffffff;");

}

void fileWidget::setFileInfoText()
{
    fileInfoLabel.setWindowFlag(Qt::FramelessWindowHint);
}

 void fileWidget::setFileOp()
 {
     fileOp.hwnd = GetDesktopWindow();
     fileOp.wFunc = FO_COPY;
     //fileOp.fFlags = FOF_NOCONFIRMATION;
 }

void fileWidget::uiInit()
{
    sa_width = this->width()/7*6;
    sa_height = this->width()/7*6/5*2;
    x_position = (this->width()-sa_width)/2;
    interval_height = this->width()/7/4;
    usedSpace =  getDirSize(default_path);

    setFileOp();
    setFileInfoText();
    setFileArea();
    setDirArea();
    setBackground();
    setPathArea();

    changeCurrentDir(default_path);
}






