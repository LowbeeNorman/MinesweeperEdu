/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#ifndef LESSON_H
#define LESSON_H

#include <QWidget>
#include "minefield.h"

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

public slots:
    void backButtonClicked ();
    ///
    /// \brief Listens for the lesson info
    /// \param topic
    /// \param currentMessage
    /// \param minefield
    ///
    void receiveLessonInfo(QString& topic, QString& currentMessage, Minefield& minefield);
signals:
    ///
    /// \brief ask the Model for the Lesson of the given number
    /// \param lessonNumber number of Lesson
    ///
    void getLesson(int lessonNumber);
};

#endif // LESSON_H
