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
    ///
    /// \brief returns the topic of this LessonLevel
    /// \return topic of this
    ///
    QString& getTopic();
    ///
    /// \brief returns the string message from the given index
    /// \param indexOfLessonGuidance index of the message from the list of messages
    /// \return message of index
    ///
    const QString& getMessageFromIndex(int indexOfLessonGuidance);
    ///
    /// \brief returns the Minefield contained in this LessonLevel
    /// \return Minefield in this
    ///
    const Minefield& getMinefield();
private:
    QString topic;
    QList<QString> lessonGuidance;
    Quiz quiz;
    Minefield* minefield;
};

#endif // LESSONLEVEL_H
