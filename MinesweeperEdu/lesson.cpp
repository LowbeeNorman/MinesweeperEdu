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
}

Lesson::~Lesson()
{
    delete ui;
}
