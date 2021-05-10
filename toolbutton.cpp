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
