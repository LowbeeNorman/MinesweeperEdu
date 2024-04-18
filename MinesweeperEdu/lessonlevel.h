/// Assignment 9: Educational App
/// CS3505
/// Written by: Kyle Stewart and Noah Sikorski
#ifndef LESSONLEVEL_H
#define LESSONLEVEL_H
#include <QString>
#include <QList>
#include <QJsonDocument>
#include "quiz.h"

class LessonLevel
{
public:
    LessonLevel(int level);
    LessonLevel();
    LessonLevel(QJsonDocument &doc);
private:
    QString topic;
    QList<QString> lessonGuidance;
    Quiz quiz;
};

#endif // LESSONLEVEL_H
