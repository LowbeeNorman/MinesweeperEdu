#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QList>

class model
{
public:
    model();

private:
    //list of tips mapped to a level
    QMap<int, QList<QString>> gameTips;
};

#endif // MODEL_H
