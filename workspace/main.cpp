#include "mainwindow.h"

#include <QApplication>
bool Debug_Mode = 1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
