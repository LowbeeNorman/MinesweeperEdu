#include "lessonlevel.h"
#include <QJsonObject>
#include <QJsonArray>

LessonLevel::LessonLevel() : m(nullptr) {}

LessonLevel::~LessonLevel() {
    if(m != nullptr)
        delete m;
}

LessonLevel::LessonLevel(QJsonDocument &doc) {
    QJsonObject obj = doc.object();

    // topic
    topic = obj.value("topic").toString();

    // lessonGuidance QStrings
    QJsonArray lessonGuidanceArr = obj.value("lessonGuidance").toArray();
    for(auto lessonGuidanceObj : lessonGuidanceArr) {
        lessonGuidance.append(lessonGuidanceObj.toString());
    }

    // Quiz
    QJsonObject quizObj = obj["quiz"].toObject();
    quiz = Quiz(quizObj);

    // LessonLevel Minefield
    QJsonArray minefieldArr = obj.value("minefield").toArray();
    bool minefield[minefieldArr.size ()] = {false};
    // Add all boolean values contained in the QJsonArray to the bool[]
    for(int i = 0; i < minefieldArr.size(); ++i) {
        minefield[i] = minefieldArr[i].toBool();
    }

    m = new Minefield(QSize(3, 3), 0.1);
}
