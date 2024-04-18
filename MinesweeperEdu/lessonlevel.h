/// Assignment 9: Educational App
/// CS3505
/// Written by: Kyle Stewart and Noah Sikorski
#ifndef LESSONLEVEL_H
#define LESSONLEVEL_H
#include <QString>
#include <QList>
#include <QJsonDocument>
#include "minefield.h"
#include "quiz.h"

class LessonLevel
{
public:
    LessonLevel(int level);
    LessonLevel();
    ///
    /// \brief constructs a LessonLevel from a given QJsonDocument
    /// \param doc
    ///
    LessonLevel(QJsonDocument &doc);
    ~LessonLevel();
private:
    QString topic;
    QList<QString> lessonGuidance;
    Quiz quiz;
    Minefield* m;
};

#endif // LESSONLEVEL_H
