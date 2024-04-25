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
    b2World world;
    b2Body* body;
    QTimer* timer = new QTimer(this);

public:
    explicit FreeplayWinScreen(QWidget *parent = nullptr);
    ~FreeplayWinScreen();
    void setUpBox2D();
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::FreeplayWinScreen *ui;
    QPainter painter;
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

    void gameLost();

    void gameWon();

    ///
    /// \brief Updates the world based on a time increment
    ///
    void updateWorld();

};

#endif // FREEPLAYWINSCREEN_H
