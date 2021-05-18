#ifndef DIALOG_H
#define DIALOG_H

#include "playwidget.h"
#include "filewidget.h"

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QString>
#include <QListView>

#include <QKeyEvent>
#include <QPainter>
#include <QDebug>

#include <QColor>

#include <QToolButton>
#include <QPixmap>
#include <QFileInfo>
#include <QFileIconProvider>

#include <QDir>
#include <QByteArray>

#include <QDesktopWidget>
#include "server.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
protected:
    Server* server;
    void keyPressEvent(QKeyEvent *event);


private:
    Ui::Dialog *ui;
    playWidget p;
    QLabel* titleLb;
    QWidget* shadowBox;
    QWidget* videoLogo;




    QPushButton* btnPlay;
    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnQuit;
    QPushButton* btnBack;

    fileWidget* mainWidget;
/*
    QWidget* mainWidget;
    QToolButton* test;
    QLabel* videoDirLb;
*/

private slots:
    void setBtn();
    void setupShadowBox();
    void setUi();
    void setMainWidget();

    void onClickedBtnPlay();


    void paintEvent(QPaintEvent *);


public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();




};

#endif // DIALOG_H
