/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#include "levelselect.h"
#include "ui_levelselect.h"
#include <cmath>

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelSelect)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    int numButtons = 15;
    int buttonWidth = 100;
    int buttonHeight = 100;
    int buffer = 10;

    for(int i = 0; i < numButtons; i++)
    {
        QPushButton *button = new QPushButton(QString::number(i + 1));
        scene->addWidget(button);

        double t = 4 * M_PI * i / (numButtons - 1);
        int x = 100 * std::sin(t) + buffer * i;
        int y = (100 + buffer) * i;

        button->setGeometry(x, y, buttonWidth, buttonHeight);
        button->setStyleSheet("background-color: rgb(0,0,255);");
        connect(button, &QPushButton::clicked, this, [this, i, button] {this->getCurrentLevel(i, button);});
    }


    connect(ui->playButton, &QPushButton::clicked, this, LevelSelect::playButtonClicked);
    connect(ui->menuButton, &QPushButton::clicked, this, LevelSelect::menuButtonClicked);
}

LevelSelect::~LevelSelect()
{
    delete ui;
}

void LevelSelect::getCurrentLevel(int levelIndex, QPushButton *button)
{
    previousButton = currentButton;
    currentButton = button;


    ui->playButton->setEnabled(true);
    ui->levelLabel->setText("Level " + QString::number(levelIndex + 1));
    currentLevel = levelIndex;
}

void LevelSelect::playButtonClicked()
{
    emit sendCurrentLevel(currentLevel);
}

void LevelSelect::menuButtonClicked()
{
    emit sendMenuClicked(0);

}




