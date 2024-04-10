/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>

namespace Ui {
class LevelSelect;
}
///
/// \brief The LevelSelect class deals with view concerns for the part of the program
/// that allows users to select a level
///
class LevelSelect : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr);
    ~LevelSelect();

private:
    Ui::LevelSelect *ui;
};

#endif // LEVELSELECT_H
