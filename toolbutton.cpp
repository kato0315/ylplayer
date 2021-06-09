#include "toolbutton.h"

toolbutton::toolbutton(QWidget *parent):QToolButton(parent)
{

}

toolbutton::~toolbutton()
{

}

void toolbutton::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){

        //qDebug() << "double click test";
        emit doubleClicked(this->text());
    }
}

void toolbutton::enterEvent(QEvent *)
{
    //qDebug() << "鼠标移入按键";
    emit enterButton();
}

void toolbutton::leaveEvent(QEvent *)
{
    //qDebug() << "鼠标移出按键";
    emit leaveButton();
}

