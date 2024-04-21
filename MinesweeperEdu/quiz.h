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

    Minefield *getMinefield ();

    ///
    /// \brief returns the string instruction from the given index
    /// \param indexOfInstruction index of the message from the list of instructions
    /// \return instruction of index
    ///
    const QString& getInstructionFromIndex(int indexOfInstruction);

    ///
    /// \brief returns the number of instructions contained in this Quiz
    /// \return num of instructions
    ///
    int getNumInstructions();
    ///
    /// \brief returns the number of correct moves the user has left to fulfill
    /// \return number of correct moves left
    ///
    int getNumCorrectMovesLeft();
    ///
    /// \brief determines if the user still has correct moves to fulfill or not
    /// \return true if the user still has moves to fulfill, false otherwise
    ///
    bool hasCorrectMovesLeft ();
private:
    QList<UserMove> correctMoves;
    QList<QString> instructions;
    Minefield *minefield;
    static const QList<QString> errorMessages;
    int numInstructions;
    int numCorrectMovesLeft;
};

#endif // QUIZ_H
