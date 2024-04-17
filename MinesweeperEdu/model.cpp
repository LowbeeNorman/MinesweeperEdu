#include "model.h"
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>

Model::Model() {
    createLessonLevels();
}

void Model::createLessonLevels() {
    for(int i = 0; i < 1; ++i) {

    }
}

LessonLevel Model::constructLessonLevelFromJSON(QString filename) {
    QJsonDocument doc;
    QFile file (filename);
    // Return nothing if file cannot be opened
    if (!file.open (QIODevice::ReadOnly)) {}
    //   TODO: return something
    // array of bytes contained in file
    QByteArray array = file.readAll ();
    doc = QJsonDocument::fromJson (array);
}
