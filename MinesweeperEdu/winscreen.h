/// Assignment 9: Educational App
/// CS3505
/// 4/19/24
/// Edited by: Caleb Norman

#ifndef WINSCREEN_H
#define WINSCREEN_H

#include <QWidget>

namespace Ui {
class WinScreen;
}

///
/// \brief This class represents all view and model components for the winscreen for each lesson
///
class WinScreen : public QWidget
{
    Q_OBJECT

public:
    explicit WinScreen(QWidget *parent = nullptr);
    ~WinScreen();

public slots:
    ///
    /// \brief Listens for the level select button to be clicked so it can notify the model
    ///
    void levelSelectButtonClicked();

    ///
    /// \brief Listens for the next lesson button to be clicked so it can notify the model
    ///
    void nextLessonButtonClicked();


signals:

    ///
    /// \brief Emitted to let all listeners know that the user wants to return to the level select
    ///
    void backToLevelSelect(int i);

    ///
    /// \brief Emitted to let all listeners know that the user wants to go to the next lesson
    ///
    void goToNextLesson();


private:
    Ui::WinScreen *ui;
};

#endif // WINSCREEN_H
