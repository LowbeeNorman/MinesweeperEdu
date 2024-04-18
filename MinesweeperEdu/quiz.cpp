#include "quiz.h"
#include <QJsonArray>

Quiz::Quiz() {}

Quiz& Quiz::operator=(Quiz rhs) {
    std::swap(correctMoves, rhs.correctMoves);
    std::swap(instructions, rhs.instructions);
    // swap Minefield's
    std::swap(m, rhs.m);
    return *this;
}

Quiz::~Quiz() {
    delete m;
}

Quiz::Quiz(QJsonObject &obj) {
    int width = obj.value("width").toInt();
    int height = obj.value("height").toInt();

    bool minefield[] = {};
    QJsonArray minefieldArr = obj.value("minefield").toArray();
    // Add all boolean values contained in the QJsonArray to the bool[]
    for(size_t i = 0; i < minefieldArr.size(); ++i) {
        minefield[i] = minefieldArr[i].toBool();
    }
    // Call method in minefield that constructs the board using the values collected.
    m = nullptr;
}
