#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QDebug>


class toolbutton :public QToolButton
{
    Q_OBJECT
public:
    toolbutton(QWidget *parent);
    ~toolbutton();
signals:
    void doubleClicked(QString);
protected:
    void mouseDoubleClickEvent(QMouseEvent *ev);
};

#endif // TOOLBUTTON_H
