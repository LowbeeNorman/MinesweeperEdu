/// Assignment 9: Educational App
/// CS3505
/// Written by: Kyle Stewart and Noah Sikorski
#ifndef QUIZ_H
#define QUIZ_H
#include <QList>
#include <QString>
#include "usermove.h"

class Quiz
{
public:
    Quiz();
    UserMove verifyUserMove(QPoint coords, UserMove::MoveType type);
private:
    QList<UserMove> correctMoves;
    QList<QString> instructions;
    static const QList<QString> errorMessages;
};

#endif // QUIZ_H
