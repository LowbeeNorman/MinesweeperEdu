#include "mainwindow.h"
#include "startscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartScreen ss;
    MainWindow w(ss);
    w.show();

    return a.exec();
}
