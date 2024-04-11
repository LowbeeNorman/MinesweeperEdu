
#ifndef LESSONLEVEL_H
#define LESSONLEVEL_H
#include <QString>
#include "usermove.h"

class LessonLevel
{
public:
    LessonLevel(int level);
    LessonLevel();
    UserMove verifyUserMove(QPoint coords, UserMove::MoveType type);
private:
    QString topic;
};

#endif // LESSONLEVEL_H
