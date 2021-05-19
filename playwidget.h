#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QDebug>

#include <QLabel>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>

#include <server.h>

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


    Server *server;
private:
    Ui::playWidget *ui;
    QLabel* lblBg;
    char cmd[1024];
    bool quit;





};

#endif // PLAYWIDGET_H
