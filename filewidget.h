#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QPaintEvent>
#include <QPainter>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QButtonGroup>
#include <QScrollArea>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <toolbutton.h>
#include <QTextBrowser>

#include <QTime>

extern "C"
{
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}


namespace Ui {
class fileWidget;
}

//const QString default_path = "//tsclient/LocalSpace";
const QString default_path = "E:/work_station/testvideo";
//const qint64 limitSpace = 1073741820;
const qint64 limitSpace = 2684354560;

class fileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit fileWidget(QWidget *parent = nullptr);
    fileWidget(int width,int height,QWidget *parent);
    ~fileWidget();

    QAbstractButton* getCheckedButton();

    QString getCurrentDirPath();
    quint64 getDirSize(const QString &path);
    QString translateDirSize(quint64 size);
    void refreshDirSize();

protected slots:
    void onDoubleClickedButton(QString text);
    void enteredFileButton(QString text);
    void enteredDirButton(QString text);
    void leftButton();

public slots:
    void onClickedBtnAdd();
    void onClickedBtnDelete();
    void onClickedBtnBack();


private:
    Ui::fileWidget *ui;

    int sa_width;
    int sa_height;
    int x_position;//左侧位置对齐
    int interval_height;

    QLabel* fileTitle;
    QLabel* dirTitle;
    QLabel* fileSpace;
    qint64  usedSpace;

    QDir* currentDir;
    QLabel* videoPathLb;

    QScrollArea* fileSa;
    QScrollArea* dirSa;
    QWidget* videoFile;
    QWidget* videoDir;

    QToolButton* fileButton;
    QButtonGroup* fileButtonGroup;
    toolbutton* dirButton;
    QButtonGroup* dirButtonGroup;

    QTextBrowser fileInfoText;
    QLabel fileInfoLabel;

    void paintEvent(QPaintEvent*);
    void setBackground();
    void setDirArea();
    void setFileArea();
    void setPathArea();
    void setFileInfoText();
    void uiInit();

    void deleteDirButton();
    void deleteFileButton();
    void createDirButton();
    void createFileButton();
    void changeCurrentDir();//后退
    void changeCurrentDir(QString dirString);

    void getVideoPreview(QFileInfo file,QToolButton* fileButton);


};



#endif // FILEWIDGET_H
