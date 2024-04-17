/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class LevelSelect;
}
///
/// \brief The LevelSelect class deals with view concerns for the part of the program
/// that allows users to select a level. This class is meant to be put into the mainwindow
///
class LevelSelect : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr);
    ~LevelSelect();
    QPushButton *previousButton = nullptr;
    QPushButton *currentButton = nullptr;

private:
    Ui::LevelSelect *ui;
    int currentLevel = 0;

public slots:
    void getCurrentLevel(int levelIndex, QPushButton *button);
    void playButtonClicked();
    void menuButtonClicked();

signals:
    void sendCurrentLevel(int levelIndex);
    void sendMenuClicked(int menuIndex);
};

#endif // LEVELSELECT_H
