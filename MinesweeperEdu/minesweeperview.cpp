#include "minesweeperview.h"

MinesweeperView::MinesweeperView (QWidget *parent)
    : QGraphicsView (parent)
    , pixmap (nullptr)
{
    mainScene = new QGraphicsScene (this);
    pixmapItem = new QGraphicsPixmapItem ();
    mainScene->addItem (pixmapItem);
    setScene (mainScene);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // load in all the images used to display the number grid
    flagImage  = new QPixmap (QString (":/images/flag.png"));
    coverImage = new QPixmap (QString (":/images/cover.png"));
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

    enabled = true;
}

MinesweeperView::~MinesweeperView ()
{
    // if the pixmap display was initialized, delete it
    if (nullptr != pixmap)
        delete pixmap;
    // delete all the preloaded images
    for (int i = 0; i < 10; ++i)
        delete numbers[i];
    delete flagImage;
    delete coverImage;
    // delete the graphics stuff
    delete pixmapItem;
    delete mainScene;
}

int MinesweeperView::pointToIndex (int x, int y)
{
    return y * size.width() + x;
}

void MinesweeperView::setBoardSize (QSize size)
{
    this->size = size;
    // initialize the pixmap and add it to the scene
    pixmap = new QPixmap (QSize (size.width () * TILE_SIZE
                               , size.height () * TILE_SIZE));
    pixmap->fill (Qt::red);
    pixmapItem->setPixmap (*pixmap);
    // zoom the view on the scene
    // this->fitInView (mainScene->sceneRect (), Qt::KeepAspectRatio);
    int width = mainScene->sceneRect ().width ();
    int height = mainScene->sceneRect ().height ();
    int maxDim = (height > width) ? height : width;
    this->scale
        (this->contentsRect ().width() / (double) maxDim
        , this->contentsRect ().width() / (double) maxDim);
    emit requestBoard ();
}

void MinesweeperView::receiveBoard (const int *board, const Tile *covers)
{
    // if the size hasn't been initialized, exit this method
    if (nullptr == pixmap)
        return;
    // pixmap->fill (Qt::transparent);
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.setCompositionMode (QPainter::CompositionMode_SourceOver);
    // go through all the tiles in the covers array and paint them to the
    // pixmap if they are not cleared.
    for (int y = 0; y < size.height (); ++y)
    {
        for (int x = 0; x < size.width (); ++x)
        {
            int index = pointToIndex (x, y);
            QPixmap *display = coverImage;
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
                display = flagImage;
                break;
            }
            painter.drawPixmap (x * TILE_SIZE, y * TILE_SIZE, *display);
        }
    }
    // set the pixmap of the pixmap item to the newly drawn pixmap
    pixmapItem->setPixmap (*pixmap);
}

// endgame stuff
void MinesweeperView::dead (QPoint where, QList<QPoint> mines)
{
    qInfo () << "dead at" << where;
}

void MinesweeperView::won (QList<QPoint> mines)
{
    qInfo () << "won";
    for (const auto &mine : mines)
    {
        flagPlaced (mine, numFlags);
    }
}

// translation methods (very helpful)
QPoint MinesweeperView::translateToMinesweeper (QPointF point)
{
    return QPoint((int) (point.x () / TILE_SIZE)
                  , (int) (point.y () / TILE_SIZE));
}

QPoint MinesweeperView::translateFromMinesweeper (QPoint point)
{
    return QPoint (point.x () * TILE_SIZE, point.y () * TILE_SIZE);
}

// stuff the mouse uses
void MinesweeperView::flagPlaced (QPoint point, int numFlags)
{
    this->numFlags = numFlags;
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.drawPixmap (translateFromMinesweeper(point), *flagImage);
    pixmapItem->setPixmap (*pixmap);
}

void MinesweeperView::flagRemoved (QPoint point, int numFlags)
{
    this->numFlags = numFlags;
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.drawPixmap (translateFromMinesweeper(point), *coverImage);
    pixmapItem->setPixmap (*pixmap);
}

void MinesweeperView::displayHighlight (QList<QPoint> coveredTiles)
{
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    for (const auto &point : prevChord)
    {
        painter.drawPixmap (translateFromMinesweeper (point), *coverImage);
    }
    for (const auto &point : coveredTiles)
    {
        painter.drawPixmap (translateFromMinesweeper (point), *numbers[0]);
    }
    prevChord = coveredTiles;
    pixmapItem->setPixmap (*pixmap);
}

void MinesweeperView::receiveIfCovered (QPoint origin, bool covered)
{
    if (!covered)
    {
        displayHighlight (QList<QPoint>());
        return;
    }
    QList<QPoint> list;
    list.append (origin);
    displayHighlight (list);
}

// mouse stuff
void MinesweeperView::mousePressEvent (QMouseEvent *event)
{
    // accept the event so it doesn't get passed to the parent
    event->accept ();

    if (enabled)
    {
        mouse = event->button ();
        QPoint minesweeperPos = translateToMinesweeper
            (mapToScene (event->pos ()));
        switch (mouse)
        {
        case Qt::LeftButton:
            // highlight this tile if it's covered
            emit requestIfCovered (minesweeperPos);
            break;
        case Qt::RightButton:
            emit flagAttempted (minesweeperPos);
            // flag/unflag this tile
            // emit flag (minesweeperPos);
            break;
        case Qt::MiddleButton:
            // highlight the covered tiles around this tile, showing the user what
            // will be cleared if there are enough flags around the point
            emit requestChord (minesweeperPos);
            break;
        default:
            break;
        }
    }
}

void MinesweeperView::mouseMoveEvent (QMouseEvent *event)
{
    // accept the event so it doesn't get passed to the parent
    event->accept ();

    // the only purpose of this method is to highlight tiles that haven't been
    // cleared yet
    QPoint minesweeperPos = translateToMinesweeper
        (mapToScene (event->pos ()));
    switch (mouse)
    {
    case Qt::LeftButton:
        emit requestIfCovered (minesweeperPos);
        break;
    case Qt::MiddleButton:
        emit requestChord (minesweeperPos);
        break;
    default:
        break;
    }
}

void MinesweeperView::mouseReleaseEvent (QMouseEvent *event)
{
    // accept the event so it doesn't get passed to the parent
    event->accept ();

    if (enabled)
    {
        // clear the highlight of the chord
        displayHighlight (QList<QPoint> ());
        QPoint minesweeperPos = translateToMinesweeper
            (mapToScene (event->pos ()));
        switch (mouse)
        {
        case Qt::LeftButton:
            // DON'T DELETE:
             emit clearAttempted (minesweeperPos);
            // clear
            // emit clear (minesweeperPos);
            break;
        case Qt::MiddleButton:
            // chord
             emit chord (minesweeperPos);
            break;
        default:
            break;
        }
    }
    // reset the mouse button
    mouse = Qt::NoButton;
}

void MinesweeperView::resizeEvent (QResizeEvent* event)
{
    qInfo () << "New size" << event->size () << "old size" << event->oldSize () << "viewport size" << contentsRect () << "scene size" << mainScene->sceneRect ();
    event->accept ();
    // zoom the view on the scene
    // this->fitInView (mainScene->sceneRect (), Qt::KeepAspectRatio);
    int width = mainScene->sceneRect ().width ();
    int height = mainScene->sceneRect ().height ();
    int maxDim = (height > width) ? height : width;
    int minViewDim = (event->size ().width() < event->size ().height ())
                     ? event->size ().width ()
                     : event->size ().height ();
    this->resetTransform ();
    this->scale
        (minViewDim / (double) maxDim
        , minViewDim / (double) maxDim);
}

void MinesweeperView::clearCell (QPoint origin)
{
    emit clear (origin);
}

void MinesweeperView::flagCell (QPoint origin)
{
    emit flag (origin);
}

void MinesweeperView::enableBoard ()
{
    enabled = true;
}

void MinesweeperView::disableBoard ()
{
    enabled = false;
}


