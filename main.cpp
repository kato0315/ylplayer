#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.connect(&a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    MainWindow w;
/*
    w.showFullScreen();
    return a.exec();
*/

    if(w.showMainWindow() ==true){
        return a.exec();
    }
    else
        return 0;

}
