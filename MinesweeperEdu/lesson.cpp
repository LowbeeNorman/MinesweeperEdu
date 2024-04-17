/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#include "lesson.h"
#include "ui_lesson.h"

Lesson::Lesson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lesson)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, Lesson::backButtonClicked);
}

Lesson::~Lesson()
{
    delete ui;
}

void Lesson::backButtonClicked()
{
    emit sendBackClicked(1);
}
