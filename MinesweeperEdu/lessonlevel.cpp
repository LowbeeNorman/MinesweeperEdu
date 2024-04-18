#include "lessonlevel.h"
#include <QJsonObject>
#include <QJsonArray>

LessonLevel::LessonLevel() {}

LessonLevel::LessonLevel(QJsonDocument &doc) {
    QJsonObject obj = doc.object();

    // topic
    topic = obj["topic"].toString();

    // lessonGuidance QStrings
    QJsonArray lessonGuidanceArr = obj["lessonGuidance"].toArray();
    for(auto lessonGuidanceObj : lessonGuidanceArr) {
        lessonGuidance.append(lessonGuidanceObj.toString());
    }

    // Quiz
    QJsonObject quizObj = obj["quiz"].toObject();
}
