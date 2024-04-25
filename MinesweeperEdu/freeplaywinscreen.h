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
};

#endif // FREEPLAYWINSCREEN_H
