#include "minesweeperview.h"

MinesweeperView::MinesweeperView (QWidget *parent = nullptr)
    : pixmap (nullptr)
{
    mainScene = new QGraphicsScene (this);
    pixmapItem = new QGraphicsPixmapItem ();
    mainScene->addItem (pixmapItem);
    setScene (mainScene);

    // load in all the images used to display the number grid
    flag = new QPixmap (QString (":/images/flag.png"));
    cover = new QPixmap (QString (":/images/cover.png"));
    numbers[0] = new QPixmap (QString (":/images/clear.png"));
    numbers[1] = new QPixmap (QString (":/images/one.png"));
    numbers[2] = new QPixmap (QString (":/images/two.png"));
    numbers[3] = new QPixmap (QString (":/images/three.png"));
    numbers[4] = new QPixmap (QString (":/images/four.png"));
    numbers[5] = new QPixmap (QString (":/images/five.png"));
    numbers[6] = new QPixmap (QString (":/images/six.png"));
    numbers[7] = new QPixmap (QString (":/images/seven.png"));
    numbers[8] = new QPixmap (QString (":/images/eight.png"));
    numbers[9] = new QPixmap (QString (":/images/mine.png"));
}

int MinesweeperView::pointToIndex (int x, int y)
{
    return y * size.width() + x;
}

void MinesweeperView::setSize (QSize size)
{
    this->size = size;
    pixmap = new QPixmap (QSize (size.width () * TILE_SIZE, size.height () * TILE_SIZE));
    pixmap->fill (Qt::transparent);
    pixmapItem->setPixmap (pixmap);
}

void MinesweeperView::receiveBoard (int *board, Tile *covers)
{
    // if the size hasn't been initialized, exit this method
    if (nullptr == pixmap)
        return;
    pixmap->fill (Qt::transparent);
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.setCompositionMode (QPainter::CompositionMode_SourceOver);
    // go through all the tiles in the covers array and paint them to the
    // pixmap if they are not cleared.
    for (int y = 0; y < size.width (); ++y)
    {
        for (int x = 0; x < size.height (); ++x)
        {
            int index = pointToIndex (x, y);
            QPixmap *display = cover;
            switch (covers[index])
            {
            case Tile::blank:
                // draw the number/bomb
                display = numbers[board[index]];
                break;
            case Tile::covered:
                // the display variable is already set to cover so there's no
                // need to update that again here
                break;
            case Tile::flagged:
                display = flag;
                break;
            }
            painter.drawPixmap (x * TILE_SIZE, y * TILE_SIZE, *display);
        }
    }
    // set the pixmap of the pixmap item to the newly drawn pixmap
    pixmapItem->setPixmap (*pixmap);
}


