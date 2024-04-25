/// Assignment 9: Educational App
/// CS3505
/// 4/24/2024
/// Written by: Caleb Norman, Winston Ji, Kyle Stewart, Jayden Ferring, Abdulahad Asim, Noah Sikorski

#ifndef LESSON_H
#define LESSON_H

#include <QWidget>
#include "minefield.h"
#include "minesweeperview.h"

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
    ///
    /// \brief Lesson constructor
    /// \param parent MainWindow
    ///
    explicit Lesson(QWidget *parent = nullptr);

    ///
    /// \brief Destructor
    ///
    ~Lesson();

    ///
    /// \brief makeConnections between lesson and Minefield
    /// \param mines in the board
    ///
    void makeConnections (Minefield &mines);

    ///
    /// \brief getBoard getter for the MinesweeperView
    /// \return MinesweeperView
    ///
    MinesweeperView* getBoard ();

private:
    ///
    /// \brief ui for Lesson
    ///
    Ui::Lesson *ui;

    ///
    /// \brief maxPage the number of pages on a particular lesson
    ///
    int maxPage = 0;

signals:
    ///
    /// \brief Requests the current state of the board
    ///
    void requestBoard ();
    ///
    /// \brief Lets listeners know that the lesson page asked to go back to the lesson select
    /// \param The number of the page to go to
    ///
    void sendBackClicked (int pageIndex);
    ///
    /// \brief Asks for the next message that needs to be displayed in the lesson, if there is one to display
    ///
    void getNextMessage ();
    ///
    /// \brief Asks for the previous message that needs to be displayed in the lesson, if there is one to display
    ///
    void getPreviousMessage ();
    ///
    /// \brief Tells the ui to update the max value on the progress bar
    /// \param The value to update the max value with
    ///
    void updateMaxProgress (int max);
    ///
    /// \brief Tells the ui to update the current value on the progress bar
    /// \param The value to update the current value with
    ///
    void updateCurrentProgress (int current);
    ///
    /// \brief Asks the model for an update on the progress of the lesson
    ///
    void requestProgressUpdate ();

public slots:
    ///
    /// \brief Listens for the level select button to be clicked
    ///
    void backButtonClicked ();
    ///
    /// \brief Listens for the next button to be clicked
    ///
    void nextButtonClicked ();
    ///
    /// \brief Listens for the previous button to be clicked
    ///
    void previousButtonClicked ();
    ///
    /// \brief Listens for the lesson info
    /// \param topic
    /// \param currentMessage
    /// \param minefield
    ///
    void receiveLessonInfo(const QString& topic, const QString& currentMessage, Minefield& minefield);
    ///
    /// \brief Listens for the next message to display
    /// \param message
    ///
    void receiveNextMessage(const QString& message);
    ///
    /// \brief Listens for the next feedback message to display
    /// \param message
    ///
    void receiveFeedback(QString message);
    ///
    /// \brief Listens for an update on the progress of the lesson
    /// \param The current progress
    /// \param The max amount
    ///
    void receiveProgressUpdate (int current, int max);

    ///
    /// \brief setFlagsRemaining updates the number of flags
    /// \param numFlags the current number of flags left
    ///
    void setFlagsRemaining(int numFlags);
};

#endif // LESSON_H
