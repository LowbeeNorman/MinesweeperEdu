/// Assignment 9: Educational App
/// CS3505
/// 4/24/24
/// Written by: Caleb Norman, Abdul Asim, Winston Ji, Kyle Stewart, Jayden Ferrin, Noah Sikorski

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

///
/// \brief The MainWindow class provides the view for the start of the program. From this window, other
/// widgets can be traded out for the current one using a stackedwidget
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model &model, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    ///
    /// \brief Updates the currently displayed page of our program
    /// \param The page index we will go to
    ///
    void updateScreenIndex(int index);

    ///
    /// \brief Listens for the currently selected level index, so that it can
    /// load the correct level when the user selects play
    /// \param Index to load, corresponds to the level number - 1
    ///
    void receiveLevelIndex(int levelIndex);

    ///
    /// \brief Listens to know if a previous game needs to be loaded in
    ///
    void loadPrevious();

    ///
    /// \brief Listens to know if the user goes from one lesson straight to the next
    ///
    void nextLessonShortcut();

    ///
    /// \brief Changes the screen to display the win screen
    ///
    void showWinScreen ();

    ///
    /// \brief Displays an error message stating the user cannot access the specified
    /// level
    ///
    void invalidLessonSelected ();

    ///
    /// \brief Allows the user to access the level
    /// level
    ///
    void validLessonSelected (int lessonNumber);

    ///
    /// \brief loads a new game
    /// \param index index
    ///
    void loadNew (int index);

signals:
    ///
    /// \brief ask the Model for the Lesson of the given number
    /// \param lessonNumber number of lesson
    ///
    void getLesson(int lessonNumber);

    ///
    /// \brief retrieves the next lesson
    ///
    void getNextLesson ();

    ///
    /// \brief checks if a user has access to the level selected
    /// \param lessonNumber number of lesson
    ///
    void checkAccess(int lessonNumber);

    ///
    /// \brief ask the Model to load in the user's progress
    ///
    void loadUserProgress ();

    ///
    /// \brief ask the Model to reset the user's progress
    ///
    void resetUserProgress ();

    ///
    /// \brief user passes a level
    ///
    void passedLevel ();
};
#endif // MAINWINDOW_H
