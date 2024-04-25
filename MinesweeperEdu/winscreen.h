/// Assignment 9: Educational App
/// CS3505
/// 4/24/24
/// Edited by: Caleb Norman, Abdul Asim

#ifndef WINSCREEN_H
#define WINSCREEN_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QPainter>

namespace Ui {
class WinScreen;
}

///
/// \brief This class represents all view and model components for the winscreen for each lesson
///
class WinScreen : public QWidget
{
    Q_OBJECT
    b2World world;
    b2Body* body;
    QTimer* timer = new QTimer(this);

public:
    explicit WinScreen(QWidget *parent = nullptr);
    ~WinScreen();
    void setUpBox2D();
    void paintEvent(QPaintEvent *event) override;

public slots:
    ///
    /// \brief Listens for the level select button to be clicked so it can notify the model
    ///
    void levelSelectButtonClicked();

    ///
    /// \brief Listens for the next lesson button to be clicked so it can notify the model
    ///
    void nextLessonButtonClicked();

    ///
    /// \brief Updates the world based on a time increment
    ///
    void updateWorld();


signals:

    ///
    /// \brief Emitted to let all listeners know that the user wants to return to the level select
    ///
    void backToLevelSelect(int i);

    ///
    /// \brief Emitted to let all listeners know that the user wants to go to the next lesson
    ///
    void goToNextLesson();


private:
    Ui::WinScreen *ui;
    QPainter painter;
    QPixmap background;
};

#endif // WINSCREEN_H
