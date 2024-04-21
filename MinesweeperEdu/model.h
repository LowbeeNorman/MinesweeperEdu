#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include "lessonlevel.h"

class Model
{
public:
    Model();

private:
    // list of tips
    QList<QString> gameTips;
    // list of all Lessons
    QList<LessonLevel> lessons;
    // number of lessons
    int numLessons;
    // current LessonLevel the user is on
    LessonLevel currentLesson;

    ///
    /// \brief Constructs all the LessonLevels for the application.
    ///
    void createLessonLevels();

    ///
    /// \brief Reads a JSON file from the given filename and returns the LessonLevel
    /// constructed from the JSON.
    /// \param filename name of the file to construct the LessonLevel from
    /// \return LessonLevel
    ///
    LessonLevel constructLessonLevelFromJSON(QString filename);

public slots:
    ///
    /// \brief Sets the LessonLevel number to the number passed.
    /// \param lessonNumber number of the LessonLevel
    ///
    void setLesson(int lessonNumber);
signals:
    ///
    /// \brief Sends the information of the current LessonLevel back to the view
    /// \param topic topic of the LessonLevel
    /// \param firstMessage first message of the LessonLevel
    /// \param minefield the minefield representing the minesweeper board for this LessonLevel
    ///
    void sendLessonInfo(QString &topic, const QString &firstMessage, const Minefield &minefield);
};

#endif // MODEL_H
