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

#include "server.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
protected:

    void keyPressEvent(QKeyEvent *event);

private:
    Server server;
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

    void onClickedBtnPlay();
    void onClickedBtnAdd();
    void onClickedBtnDelete();

    void paintEvent(QPaintEvent *);


public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();




};

#endif // DIALOG_H
