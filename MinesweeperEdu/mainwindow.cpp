/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"

MainWindow::MainWindow(StartScreen &startScreen, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&startScreen, &StartScreen::sendNewLessonClicked, this, &MainWindow::updateScreenIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScreenIndex(int index)
{
    qDebug() << "HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
}


