#ifndef LESSON_H
#define LESSON_H

#include <QWidget>

namespace Ui {
class Lesson;
}

class Lesson : public QWidget
{
    Q_OBJECT

public:
    explicit Lesson(QWidget *parent = nullptr);
    ~Lesson();

private:
    Ui::Lesson *ui;
};

#endif // LESSON_H
