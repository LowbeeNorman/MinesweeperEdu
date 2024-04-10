#include "mainwindowsecond.h"
#include "ui_mainwindowsecond.h"

MainWindowSecond::MainWindowSecond(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowSecond)
{
    ui->setupUi(this);
}

MainWindowSecond::~MainWindowSecond()
{
    delete ui;
}
