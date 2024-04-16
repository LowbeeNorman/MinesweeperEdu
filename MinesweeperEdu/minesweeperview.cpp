#include "minesweeperview.h"

MinesweeperView::MinesweeperView (QWidget *parent = nullptr)
    : pixmap (nullptr)
{
    mainScene = new QGraphicsScene (this);
    pixmapItem = new QGraphicsPixmapItem ();
    mainScene->addItem (pixmapItem);
    setScene (mainScene);
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
            QString imageAddress (":/images/");
            switch (covers[index])
            {
            case Tile::blank:
                // draw the number/bomb
                switch (board[index])
                {
                case 0:
                    imageAddress.append ("clear.png");
                    break;
                case 1:
                    imageAddress.append ("one.png");
                    break;
                case 2:
                    imageAddress.append ("two.png");
                    break;
                case 3:
                    imageAddress.append ("three.png");
                    break;
                case 4:
                    imageAddress.append ("four.png");
                    break;
                case 5:
                    imageAddress.append ("five.png");
                    break;
                case 6:
                    imageAddress.append ("six.png");
                    break;
                case 7:
                    imageAddress.append ("seven.png");
                    break;
                case 8:
                    imageAddress.append ("eight.png");
                    break;
                default:
                    imageAddress.append ("mine.png");
                    break;
                }
                break;
            case Tile::covered:
                imageAddress.append ("cover.png");
                break;
            case Tile::flagged:
                imageAddress.append ("flag.png");
                break;
            }
            painter.drawPixmap (x * TILE_SIZE, y * TILE_SIZE, QPixmap (imageAddress));
        }
    }
    // set the pixmap of the pixmap item to the newly drawn pixmap
    pixmapItem->setPixmap (*pixmap);
}


