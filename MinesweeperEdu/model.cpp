#include "model.h"
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>

Model::Model() {
    numLessons = 12;
    createLessonLevels();
    currentLesson = lessons.at(0);
}

void Model::createLessonLevels() {
    for(int i = 1; i <= numLessons; ++i)
        lessons.append
            (constructLessonLevelFromJSON (QString (":/json/lesson").append(QString::number(i)).append(".json")));
}

LessonLevel Model::constructLessonLevelFromJSON(QString filename) {
    QJsonDocument doc;
    QFile file (filename);
    // Return nothing if file cannot be opened
    if (!file.open (QIODevice::ReadOnly)) {
        return LessonLevel();
    }
    //   TODO: return something
    // array of bytes contained in file
    QByteArray array = file.readAll ();
    doc = QJsonDocument::fromJson (array);
    return LessonLevel(doc);
}

void Model::setLesson(int lessonNumber) {
    currentLesson = lessons.at(lessonNumber);
    //emit sendLessonInfo(currentLesson.getTopic(), currentLesson.getMessageFromIndex(0), currentLesson.getMinefield());
}
