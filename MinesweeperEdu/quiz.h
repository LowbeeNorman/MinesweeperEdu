/// Assignment 9: Educational App
/// CS3505
/// Written by: Kyle Stewart and Noah Sikorski
#ifndef QUIZ_H
#define QUIZ_H
#include <QList>
#include <QString>
#include <QJsonObject>
#include "minefield.h"
#include "usermove.h"

class Quiz
{
public:
    Quiz();
    Quiz (const Quiz &other);
    ///
    /// \brief constructs a Quiz from the given QJsonObject
    /// \param obj
    ///
    Quiz(QJsonObject &obj);
    ///
    /// \brief assignment operator
    /// \param rhs
    /// \return
    ///
    Quiz& operator=(Quiz rhs);
    ~Quiz();
    UserMove verifyUserMove(QPoint coords, UserMove::MoveType type);
private:
    QList<UserMove> correctMoves;
    QList<QString> instructions;
    Minefield *m;
    static const QList<QString> errorMessages;
};

#endif // QUIZ_H
