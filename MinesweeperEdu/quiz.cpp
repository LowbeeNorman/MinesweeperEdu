#include "quiz.h"
#include <QJsonArray>

Quiz::Quiz() : m(nullptr) {}

Quiz& Quiz::operator=(Quiz rhs) {
    std::swap(correctMoves, rhs.correctMoves);
    std::swap(instructions, rhs.instructions);
    // swap minefields
    std::swap(m, rhs.m);
    return *this;
}

Quiz::Quiz (const Quiz &other)
    : correctMoves (other.correctMoves)
    , instructions (other.instructions)
{
    m = new Minefield (*other.m);
}

Quiz::~Quiz() {
    if(m != nullptr)
        delete m;
}

Quiz::Quiz(QJsonObject &obj) {
    int width = obj.value("width").toInt();
    int height = obj.value("height").toInt();

    QJsonArray minefieldArr = obj.value("minefield").toArray();
    bool minefield[minefieldArr.size ()] = {false};
    // Add all boolean values contained in the QJsonArray to the bool[]
    for(int i = 0; i < minefieldArr.size (); ++i) {
        minefield[i] = minefieldArr[i].toBool();
    }
    // Call method in minefield that constructs the board using the values collected.
    m = new Minefield(QSize(width, height), 0.15f);
}
