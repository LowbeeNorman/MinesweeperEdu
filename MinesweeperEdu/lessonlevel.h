/// Assignment 9: Educational App
/// CS3505
/// Written by: Kyle Stewart and Noah Sikorski
#ifndef LESSONLEVEL_H
#define LESSONLEVEL_H
#include <QString>
#include <QList>
#include "usermove.h"
#include "quiz.h"

class LessonLevel
{
public:
    LessonLevel(int level);
    LessonLevel();
    UserMove verifyUserMove(QPoint coords, UserMove::MoveType type);
private:
    QString topic;
    QList<QString> lessonGuidance;
    Quiz quiz;
};

#endif // LESSONLEVEL_H
