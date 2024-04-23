/// Assignment 9: Educational App
/// CS3505
/// 4/16/24
/// Written by: Caleb Norman, Abdul Asim

#include "levelselect.h"
#include "ui_levelselect.h"
#include <cmath>

#include <QImageWriter>
#include <QAbstractButton>
#include <QScrollBar>

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelSelect)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(ui->graphicsView);
    QPixmap backgroundImage(QString (":/images/blurryPath.png"));
    pixmapItem = new QGraphicsPixmapItem(backgroundImage);
    pixmapItem->setZValue(-1);
    scene->addItem(pixmapItem);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(pixmapItem->boundingRect());

    // create the group to add buttons to
    group = new QButtonGroup (ui->verticalLayout);
    group->setExclusive (true);

    int numButtons = 20;
    int buttonWidth = 100;
    int buttonHeight = 100;
    int buffer = 40;

    QString imagePath ("image.jpg");
    QImage image = QPixmap (QString (":/images/level1.png"))
                       .mask ()
                       .toImage ();
    {
        QImageWriter writer (imagePath);
        writer.write (image);
    }

    for(int i = 0; i <= numButtons; i++)
    {
        QPushButton *button = new QPushButton();
        scene->addWidget(button);

        if (i == 0)
        {
            button->hide ();
            button->setDisabled (true);
            continue;
        }

        double t = 4 * M_PI * i / (numButtons - 1);
        int x = buttonWidth * std::sin(t) * 2;
        int y = (buttonHeight + buffer) * i;

        button->setGeometry(x + 350, y, buttonWidth, buttonHeight);

        // make it pretty
        button->setStyleSheet (QString (
            "QPushButton {"
                "background: transparent;"
                "border: 6px solid white;"
                "border-radius: 6px;"
                "border-image: url(\":/images/level%1.png\");"
            "}"
            "QPushButton:hover {"
                "background: orange;"
                "border: 4px solid orange;"
                "border-radius: 4px;"
            "}"
            "QPushButton:checked {"
                "background: green;"
                "border: 4px solid green;"
                "border-radius: 4px;"
            "}"
        ).arg(i));
        // set the mask so it looks right and stuff
        button->setMask (QPixmap (QString (":/images/level1.png"))
                            .scaled (button->size ())
                            .mask ());
        // Set the button to checkable so it shows which button is currently
        // selected
        button->setCheckable (true);
        // Add the button to the group with id i
        group->addButton (button, i);
    }
    ui->graphicsView->verticalScrollBar()->setSliderPosition(1);

    connect (group, &QButtonGroup::buttonToggled
            , this, &LevelSelect::getCurrentLevel);
    connect(ui->playButton, &QPushButton::clicked
            , this, &LevelSelect::playButtonClicked);
    connect(ui->menuButton, &QPushButton::clicked
            , this, &LevelSelect::menuButtonClicked);
}

LevelSelect::~LevelSelect()
{
    delete ui;
    delete pixmapItem;
}

void LevelSelect::getCurrentLevel (QAbstractButton *button, bool checked)
{
    if (!checked)
        return;
    currentButton = static_cast<QPushButton *> (button);

    ui->playButton->setEnabled(true);
    currentLevel = group->checkedId ();
    qInfo () << "currentLevel:" << currentLevel;
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
        // currentButton->setStyleSheet("background-color: rgb(0,0,255);");
    }
    currentButton = nullptr;
    ui->levelLabel->clear();

    // If we lock levels not unlocked yet, that needs to be changed in here!
}

void LevelSelect::updateCurrentLevel(int levelIndex)
{

    if (currentLevel != 0) {
        QPushButton *button = static_cast<QPushButton *>(group->button(currentLevel));
        if (button) {
            button->setChecked(false);
        }
    }

    currentLevel = levelIndex;

    if (currentLevel != 0) {
        QPushButton *button = static_cast<QPushButton *>(group->button(currentLevel));
        if (button) {
            button->setChecked(true);
        }
    }
}




