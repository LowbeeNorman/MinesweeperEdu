/// Assignment 9: Educational App
/// CS3505
/// 4/19/24
/// Edited by: Caleb Norman
///
#include "winscreen.h"
#include "ui_winscreen.h"

WinScreen::WinScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WinScreen)
{
    ui->setupUi(this);

    connect(ui->levelSelectButton, &QPushButton::clicked, this, &WinScreen::levelSelectButtonClicked);
    connect(ui->nextLessonButton, &QPushButton::clicked, this, &WinScreen::nextLessonButtonClicked);
}

WinScreen::~WinScreen()
{
    delete ui;
}

void WinScreen::levelSelectButtonClicked()
{
    emit backToLevelSelect(1);
}

void WinScreen::nextLessonButtonClicked()
{
    emit goToNextLesson();
}
