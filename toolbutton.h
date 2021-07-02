#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
//#include <QDebug>


class toolbutton :public QToolButton
{
    Q_OBJECT
public:
    toolbutton(QWidget *parent);
    ~toolbutton();
signals:
    void doubleClicked(QString);
    void enterButton(QString);
    void leaveButton();
protected:
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // TOOLBUTTON_H
