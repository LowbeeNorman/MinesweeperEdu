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
    LessonLevel ();

    ///
    /// \brief constructs a LessonLevel from a given QJsonDocument
    /// \param doc
    ///
    LessonLevel (QJsonDocument &doc, Minefield *minefield);

    LessonLevel (const LessonLevel &other);
    ~LessonLevel ();
    LessonLevel &operator= (LessonLevel other);

    ///
    /// \brief returns the topic of this LessonLevel
    /// \return topic of this
    ///
    const QString &getTopic();
    ///
    /// \brief returns the string message from the given index
    /// \param indexOfLessonGuidance index of the message from the list of messages
    /// \return message of index
    ///
    const QString &getMessageFromIndex(int indexOfLessonGuidance);
    ///
    /// \brief returns the string instruction from the given index
    /// \param indexOfInstruction index of the message from the list of instructions
    /// \return instruction of index
    ///
    const QString &getInstructionFromIndex(int indexOfInstruction);
    ///
    /// \brief returns the Minefield contained in this LessonLevel
    /// \return Minefield in this
    ///
    Minefield &getMinefield();
    ///
    /// \brief returns the number of messages this LessonLevel contains
    /// \return number of messages
    ///
    int getNumMessages();
    ///
    /// \brief returns the number of instructions the Quiz within this LessonLevel contains
    /// \return number of instructions
    ///
    int getNumInstructions ();
    ///
    /// \brief returns the number of correct moves the user has left to fulfill
    /// \return number of correct moves left
    ///
    int getNumCorrectMovesLeft ();
    ///
    /// \brief determines if the user still has correct moves to fulfill or not
    /// \return true if the user still has moves to fulfill, false otherwise
    ///
    bool hasCorrectMovesLeft ();
    ///
    /// \brief checks if the given move at the given origin is the correct move
    /// \param origin cell clicked
    /// \param type FLAG or CLEAR
    /// \return true if the correct move, false otherwise
    ///
    bool checkMove(QPoint origin, UserMove::MoveType type);
private:
    QString topic;
    QList<QString> lessonGuidance;
    Quiz quiz;
    int numMessages;
};

#endif // LESSONLEVEL_H
