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

private:
    Ui::playWidget *ui;
    QLabel* lblBg;



};

#endif // PLAYWIDGET_H
