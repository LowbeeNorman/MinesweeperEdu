#include "lessonlevel.h"
#include <QJsonObject>
#include <QJsonArray>

LessonLevel::LessonLevel()
    : quiz (nullptr)
    // , minefield (nullptr)
{}

LessonLevel::LessonLevel(QJsonDocument &doc) {
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
    quiz = new Quiz(quizObj);

    // LessonLevel Minefield
    // minefield = quiz->getMinefield ();
}

LessonLevel::LessonLevel (const LessonLevel &other)
    : topic (other.topic)
    , lessonGuidance (other.lessonGuidance)
    // , minefield (nullptr)
    , numMessages (other.numMessages)
{
    quiz = new Quiz (*other.quiz);
    // minefield = quiz->getMinefield ();
}

LessonLevel::~LessonLevel ()
{
    if (nullptr != quiz)
        delete quiz;
}

LessonLevel &LessonLevel::operator= (LessonLevel other)
{
    std::swap (topic, other.topic);
    std::swap (lessonGuidance, other.lessonGuidance);
    std::swap (quiz, other.quiz);
    // std::swap (minefield, other.minefield);
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
    return quiz->getInstructionFromIndex(indexOfInstruction);
}

Minefield& LessonLevel::getMinefield() {
    return *quiz->getMinefield ();
}

int LessonLevel::getNumMessages()
{
    return numMessages;
}

int LessonLevel::getNumInstructions ()
{
    return quiz->getNumInstructions();
}

int LessonLevel::getNumCorrectMovesLeft ()
{
    return quiz->getNumCorrectMovesLeft();
}

bool LessonLevel::hasCorrectMovesLeft ()
{
    return quiz->hasCorrectMovesLeft();
}

bool LessonLevel::checkMove (QPoint origin, UserMove::MoveType type)
{
    return quiz->verifyUserMove(origin, type);
}
