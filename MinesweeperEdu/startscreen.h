/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>

namespace Ui {
class StartScreen;
}

///
/// \brief The StartScreen class deals with view concerns for the part of the program
/// that allows users to start a new game or continue the same one. This class is meant
/// to be put into the mainwindow
///
class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

private:
    Ui::StartScreen *ui;
};

#endif // STARTSCREEN_H
