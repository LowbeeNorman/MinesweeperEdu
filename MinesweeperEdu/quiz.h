/// Assignment 9: Educational App
/// CS3505
/// Written by: Kyle Stewart and Noah Sikorski
#ifndef QUIZ_H
#define QUIZ_H
#include <QList>
#include <QString>

class Quiz
{
public:
    Quiz();
private:
    QList<QString> instructions;
};

#endif // QUIZ_H
