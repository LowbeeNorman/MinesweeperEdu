// Assignment 9: Educational App
// CS3505
// 4/12/24
// Written by: Caleb Norman

#include "mainwindow.h"
#include "minefield.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minefield mines (QSize (15, 15), 0.15f);
    MainWindow w;
    w.makeConnections (mines);
    w.show();

    return a.exec();
}
