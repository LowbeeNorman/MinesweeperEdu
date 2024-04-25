#ifndef FREEPLAYWINSCREEN_H
#define FREEPLAYWINSCREEN_H

#include <QWidget>

namespace Ui {
class FreeplayWinScreen;
}

class FreeplayWinScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FreeplayWinScreen(QWidget *parent = nullptr);
    ~FreeplayWinScreen();

private:
    Ui::FreeplayWinScreen *ui;

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
public slots:
    ///
    /// \brief Listens for the menu button to be clicked
    ///
    void menuButtonClicked();
    ///
    /// \brief Listens for the next button to be clicked
    ///
    void nextButtonClicked();

};

#endif // FREEPLAYWINSCREEN_H
