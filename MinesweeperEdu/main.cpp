// Assignment 9: Educational App
// CS3505
// 4/12/24
// Written by: Caleb Norman

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m;
    MainWindow w (m);
    w.show();

    return a.exec();
}
