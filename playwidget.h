#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QCloseEvent>


#include <QLabel>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>

#include "server.h"

//#include <QDebug>


namespace Ui {
class playWidget;
}

class playWidget : public QWidget
{
    Q_OBJECT



private slots:
    void setWidgetUi();
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *);

public:
    explicit playWidget(QWidget *parent = 0);
    ~playWidget();

    void setServer(Server *s);

private:
    Ui::playWidget *ui;
    QLabel* lblBg;
    char cmd[1024];
    bool quit;
    Server *server;

};

#endif // PLAYWIDGET_H
