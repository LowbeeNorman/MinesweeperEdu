#include "levelselect.h"
#include "ui_levelselect.h"

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelSelect)
{
    ui->setupUi(this);
}

LevelSelect::~LevelSelect()
{
    delete ui;
}
