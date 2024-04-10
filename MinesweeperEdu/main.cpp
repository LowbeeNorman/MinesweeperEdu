#include "mainwindow.h"
#include "levelselect.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    LevelSelect l;
    l.show();
    return a.exec();
}
