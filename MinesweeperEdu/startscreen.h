/// Assignment 9: Educational App
/// CS3505
/// 4/16/24
/// Written by: Caleb Norman, Abdul Asim

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

public slots:
    ///
    /// \brief This slot will receive the signal from the new lesson button
    /// that resides within the ui
    ///
    void newLessonButtonClicked();

    ///
    /// \brief This slot will receive the signal from the continue button
    /// that resides within the ui
    ///
    void continueButtonClicked();

signals:
    ///
    /// \brief This signal notifies any listeners that the newLessonButton has been clicked,
    /// and the page should be updated
    /// \param The index of the page to move to
    ///
    void sendNewLessonClicked(int index);

    ///
    /// \brief This signal notifies any listeners that the continueButton has been clicked,
    /// and the page should be updated
    ///
    void sendContinueClicked();

    ///
    /// \brief This signal will let the levelselect know that it should reset it's view,
    /// because a new game has been started
    ///
    void startingNewGame();


private:
    Ui::StartScreen *ui;
};

#endif // STARTSCREEN_H
