/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#ifndef LESSON_H
#define LESSON_H

#include <QWidget>

namespace Ui {
class Lesson;
}

///
/// \brief The Lesson class deals with view concerns for the part of the program
/// that allows users to learn inside of a level. This class is meant to be put into the mainwindow
///
class Lesson : public QWidget
{
    Q_OBJECT

public:
    explicit Lesson(QWidget *parent = nullptr);
    ~Lesson();

private:
    Ui::Lesson *ui;

public slots:
    void backButtonClicked();

signals:
    void sendBackClicked(int pageIndex);
};

#endif // LESSON_H
