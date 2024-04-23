/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

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
    explicit Lesson(QWidget *parent = nullptr);
    ~Lesson();

    void makeConnections (Minefield &mines);

private:
    Ui::Lesson *ui;

signals:
    void requestBoard ();
    void sendBackClicked (int pageIndex);
    void getNextMessage ();
    void getPreviousMessage ();

public slots:
    void backButtonClicked ();
    void nextButtonClicked ();
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

    MinesweeperView* getBoard ();
};

#endif // LESSON_H
