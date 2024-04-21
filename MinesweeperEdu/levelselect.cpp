/// Assignment 9: Educational App
/// CS3505
/// 4/16/24
/// Written by: Caleb Norman, Abdul Asim

#include "levelselect.h"
#include "ui_levelselect.h"
#include <cmath>

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelSelect)
{
    ui->setupUi(this);


    QGraphicsScene *scene = new QGraphicsScene();

    int numButtons = 20;
    int buttonWidth = 100;
    int buttonHeight = 100;
    int buffer = 40;

    for(int i = 0; i <= numButtons; i++)
    {
        QPushButton *button = new QPushButton(QString::number(i));
        scene->addWidget(button);

        if (i == 0) {
            button->hide();
            button->setDisabled(true);
        }

        double t = 4 * M_PI * i / (numButtons - 1);
        int x = buttonWidth * std::sin(t) * 2;
        int y = (buttonHeight + buffer) * i;

        button->setGeometry(x + 350, y, buttonWidth, buttonHeight);
        button->setStyleSheet("background-color: rgb(0,0,255);");
        connect(button, &QPushButton::clicked, this, [this, i, button] {this->getCurrentLevel(i, button);});
    }

    QPixmap backgroundImage(QString (":/images/blurryPath.png"));
    pixmapItem = new QGraphicsPixmapItem(backgroundImage);
    pixmapItem->setZValue(-1);
    scene->addItem(pixmapItem);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(pixmapItem->boundingRect());

    connect(ui->playButton, &QPushButton::clicked, this, &LevelSelect::playButtonClicked);
    connect(ui->menuButton, &QPushButton::clicked, this, &LevelSelect::menuButtonClicked);
}

LevelSelect::~LevelSelect()
{
    delete ui;
}

void LevelSelect::getCurrentLevel(int levelIndex, QPushButton *button)
{
    if(currentButton != nullptr)
    {
        currentButton->setStyleSheet("background-color: rgb(0,0,255);");
    }
    currentButton = button;
    currentButton->setStyleSheet("background-color: rgb(0,255,255);");

    ui->playButton->setEnabled(true);
    ui->levelLabel->setText("Level " + QString::number(levelIndex));
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

void LevelSelect::receiveStartingNewGame()
{
    qDebug() << "Need to delete all old saved progress";

    ui->playButton->setEnabled(false);
    if(currentButton != nullptr)
    {
        currentButton->setStyleSheet("background-color: rgb(0,0,255);");
    }
    currentButton = nullptr;
    ui->levelLabel->clear();

    // If we lock levels not unlocked yet, that needs to be changed in here!
}




