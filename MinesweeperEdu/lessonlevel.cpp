#include "lessonlevel.h"
#include <QJsonObject>
#include <QJsonArray>

LessonLevel::LessonLevel() : minefield(nullptr) {}

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
    quiz = Quiz(quizObj);

    // LessonLevel Minefield
    minefield = quiz.getMinefield ();
}

const QString& LessonLevel::getTopic() {
    return topic;
}

const QString& LessonLevel::getMessageFromIndex(int indexOfLessonGuidance) {
    return lessonGuidance.at(indexOfLessonGuidance);
}

Minefield& LessonLevel::getMinefield() {
    return *minefield;
}

int LessonLevel::getNumMessages()
{
    return numMessages;
}
