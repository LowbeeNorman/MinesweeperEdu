/// Assignment 9: Educational App
/// CS3505
/// 4/24/24
/// Edited by: Caleb Norman, Abdul Asim, Winston Ji

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
    ///
    /// \brief WinScreen default constructor for the winscreen
    /// \param parent widget to be passed to the base constructor
    ///
    explicit WinScreen(QWidget *parent = nullptr);
    ~WinScreen();
    ///
    /// \brief setUpBox2D sets up the box2d for the bouncing image
    ///
    void setUpBox2D();
    ///
    /// \brief paintEvent handles painting to the screen
    /// \param event the event passed to paint
    ///
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

    ///
    /// \brief Disables the Next Lesson button
    ///
    void disableNextButton();

    ///
    /// \brief Enables the Next Lesson button
    ///
    void enableNextButton();

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
