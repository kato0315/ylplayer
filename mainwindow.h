#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playwidget.h"
#include "filewidget.h"
#include "server.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QString>
#include <QKeyEvent>
#include <QPainter>
#include <QColor>
#include <QDesktopWidget>
#include <QTimer>
#include <QInputDialog>

#include "libavformat/avformat.h"

//#include <QDebug>


class MainWindow : public QWidget
{
    Q_OBJECT
protected:
    Server* server;
    void keyPressEvent(QKeyEvent *event);


private:
    QLabel* titleLb;
    QWidget* shadowBox;

    QPushButton* btnPlay;
    QPushButton* btnPlayHttp;
    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnQuit;
    QPushButton* btnBack;

    fileWidget* mainWidget;
    playWidget p;


private slots:
    void setBtn();
    void setupShadowBox();
    void setUi();
    void setFileWidget();
    void setPlayWidget();

    void onClickedBtnPlay();
    void onClickedBtnPlayHttp();
    void sendMsgSlot();
    void sendUrlSlot(QString url);

    void paintEvent(QPaintEvent *);


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool showMainWindow();

};

#endif // MAINWINDOW_H
