#ifndef DIALOG_H
#define DIALOG_H

#include "playwidget.h"
#include "filewidget.h"
#include "server.h"

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QString>
#include <QKeyEvent>
#include <QPainter>
#include <QColor>
#include <QDesktopWidget>
#include <QTimer>

//#include <QDebug>


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
    QLabel* titleLb;
    QWidget* shadowBox;

    QPushButton* btnPlay;
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
    void sendMsgSlot();

    void paintEvent(QPaintEvent *);


public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void showDialog();

};

#endif // DIALOG_H
