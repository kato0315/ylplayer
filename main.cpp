#include "dialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.connect(&a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    Dialog w; 

    w.showFullScreen();
    //w.showDialog();

    return a.exec();
}
