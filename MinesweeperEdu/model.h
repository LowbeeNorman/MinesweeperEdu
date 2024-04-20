#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include "lessonlevel.h"

class Model
{
public:
    Model();

private:
    //list of tips
    QList<QString> gameTips;
    //list of all Lessons
    QList<LessonLevel> lessons;
    //number of lessons
    int numLessons;

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
};

#endif // MODEL_H
