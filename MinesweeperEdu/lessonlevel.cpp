#include "lessonlevel.h"
#include <QJsonObject>
#include <QJsonArray>

LessonLevel::LessonLevel () {}

LessonLevel::LessonLevel (QJsonDocument &doc, Minefield *minefield) {
    QJsonObject obj = doc.object();

    // topic
    topic = obj.value("topic").toString();

    // lessonGuidance QStrings
    QJsonArray lessonGuidanceArr = obj.value("lessonGuidance").toArray();
    for(auto lessonGuidanceObj : lessonGuidanceArr) {
        lessonGuidance.append(lessonGuidanceObj.toString());
    }

    numMessages = lessonGuidanceArr.size();

    // Quiz
    QJsonObject quizObj = obj["quiz"].toObject();
    quiz = Quiz(quizObj, minefield);
}

LessonLevel::LessonLevel (const LessonLevel &other)
    : topic (other.topic)
    , lessonGuidance (other.lessonGuidance)
    , quiz (other.quiz)
    , numMessages (other.numMessages)
{}

LessonLevel::~LessonLevel () {}

LessonLevel &LessonLevel::operator= (LessonLevel other)
{
    std::swap (topic, other.topic);
    std::swap (lessonGuidance, other.lessonGuidance);
    std::swap (quiz, other.quiz);
    std::swap (numMessages, other.numMessages);
    return *this;
}

const QString& LessonLevel::getTopic() {
    return topic;
}

const QString& LessonLevel::getMessageFromIndex(int indexOfLessonGuidance) {
    return lessonGuidance.at(indexOfLessonGuidance);
}

const QString& LessonLevel::getInstructionFromIndex(int indexOfInstruction)
{
    return quiz.getInstructionFromIndex(indexOfInstruction);
}

Minefield &LessonLevel::getMinefield() {
    return *quiz.getMinefield ();
}

int LessonLevel::getNumMessages()
{
    return numMessages;
}

int LessonLevel::getNumInstructions ()
{
    return quiz.getNumInstructions();
}

int LessonLevel::getNumCorrectMovesLeft ()
{
    return quiz.getNumCorrectMovesLeft();
}

bool LessonLevel::hasCorrectMovesLeft ()
{
    return quiz.hasCorrectMovesLeft();
}

bool LessonLevel::checkMove (QPoint origin, UserMove::MoveType type)
{
    return quiz.verifyUserMove(origin, type);
}

void LessonLevel::executeMovesAtIndex (int index)
{
    quiz.executeMovesAtIndex(index);
}
