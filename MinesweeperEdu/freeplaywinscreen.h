/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/24
/// Written by: Caleb Norman, Winston Ji, Jayden Ferrin, Abdulahad Asim

#ifndef FREEPLAYWINSCREEN_H
#define FREEPLAYWINSCREEN_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QPainter>

namespace Ui {
class FreeplayWinScreen;
}

class FreeplayWinScreen : public QWidget
{
    Q_OBJECT
    // Members for Box2D
    b2World world;
    b2Body* body;
    QTimer* timer = new QTimer(this);

public:
    ///
    /// \brief FreeplayWinScreen constructor
    /// \param parent MainWindow
    ///
    explicit FreeplayWinScreen(QWidget *parent = nullptr);

    ///
    /// \brief Destructor
    ///
    ~FreeplayWinScreen();

    ///
    /// \brief setUpBox2D initializes Box2D physics
    ///
    void setUpBox2D();

    ///
    /// \brief paintEvent paints pixmaps onto the canvas
    /// \param event the paint event
    ///
    void paintEvent(QPaintEvent *event) override;

private:
    ///
    /// \brief ui for the FreeplayWinScreen
    ///
    Ui::FreeplayWinScreen *ui;

    ///
    /// \brief painter paints onto the canvas
    ///
    QPainter painter;

    ///
    /// \brief background stores the Pixmap for the background image
    ///
    QPixmap background;

signals:
    ///
    /// \brief Returns to the menu
    /// \param Index of the menu
    ///
    void returnToMenu(int i);
    ///
    /// \brief Returns to the freeplay, with another menu loaded
    /// \param Index of the freeplay screen
    ///
    void nextFreeplayLevel(int i);

    ///
    /// \brief newBoard generates a new random board
    ///
    void newBoard();

public slots:
    ///
    /// \brief Listens for the menu button to be clicked
    ///
    void menuButtonClicked();

    ///
    /// \brief Listens for the next button to be clicked
    ///
    void nextButtonClicked();

    ///
    /// \brief gameLost emitted when the player loses
    ///
    void gameLost();

    ///
    /// \brief gameWon emitted when the player wins
    ///
    void gameWon();

    ///
    /// \brief Updates the world based on a time increment
    ///
    void updateWorld();


};

#endif // FREEPLAYWINSCREEN_H
