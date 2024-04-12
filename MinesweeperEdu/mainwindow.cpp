/// Assignment 9: Educational App
/// CS3505
/// 4/12/24
/// Written by: Caleb Norman

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // This connection is sent from the startPage widget that resides within the mainwindow, and is received by
    // the main window. This will be a common pattern within our program with various widgets within the main window
    connect(ui->startPage, &StartScreen::sendNewLessonClicked, this, &MainWindow::updateScreenIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScreenIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}


