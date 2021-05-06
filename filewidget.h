#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>

#include <QToolButton>
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QPaintEvent>
#include <QPainter>
#include <QDir>
#include <QString>
#include <QDebug>

#include <QButtonGroup>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>

#include <toolbutton.h>

namespace Ui {
class fileWidget;
}

const QString default_path = "E:/work_station/testvideo";

class fileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit fileWidget(QWidget *parent = nullptr);
    ~fileWidget();

    QAbstractButton* getCheckedButton();



protected slots:
    void onDoubleClickedButton();

    void test01();
private:
    Ui::fileWidget *ui;


    QLabel* fileTitle;
    QLabel* dirTitle;

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

    void paintEvent(QPaintEvent*);
    void setBackground();
    void setDirArea();
    void setFileArea();
    void setPathArea();
    void uiInit();

    void deleteDirButton();
    void changeDirButton();
    void changeCurrentDir(QString dirString);


};



#endif // FILEWIDGET_H
