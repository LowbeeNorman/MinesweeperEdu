/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Jayden Ferrin, Winston Ji

#include "minesweeperview.h"

MinesweeperView::MinesweeperView (QWidget *parent)
    : QGraphicsView (parent)
    , size (0, 0)
    , pixmap (nullptr)
    , flagImage      (QString (":/images/flag.png"))
    , coverImage     (QString (":/images/cover.png"))
    , redHighlight   (QString (":/images/redFrame.png"))
    , orangeHighlight(QString (":/images/orangeFrame.png"))
    , yellowHighlight(QString (":/images/yellowFrame.png"))
    , pinkHighlight  (QString (":/images/pinkFrame.png"))
    , blueHighlight  (QString (":/images/blueFrame.png"))
    , purpleHighlight(QString (":/images/purpleFrame.png"))
    , brownHighlight (QString (":/images/brownFrame.png"))
    , blackHighlight (QString (":/images/blackFrame.png"))
    , numbers {QString (":/images/clear.png")
               , QString (":/images/one.png")
               , QString (":/images/two.png")
               , QString (":/images/three.png")
               , QString (":/images/four.png")
               , QString (":/images/five.png")
               , QString (":/images/six.png")
               , QString (":/images/seven.png")
               , QString (":/images/eight.png")
               , QString (":/images/mine.png")}
    , enabled (true)
{
    mainScene = new QGraphicsScene (this);
    pixmapItem = new QGraphicsPixmapItem ();
    mainScene->addItem (pixmapItem);
    setScene (mainScene);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MinesweeperView::~MinesweeperView ()
{
    // if the pixmap display was initialized, delete it
    if (nullptr != pixmap)
        delete pixmap;
    delete pixmapItem;
    delete mainScene;
}

int MinesweeperView::pointToIndex (int x, int y)
{
    return y * size.width() + x;
}

void MinesweeperView::internalResize ()
{
    // set the scene rect to the pixmap rect since that is all that is
    // rendered in the view
    if (nullptr == pixmap)
    {
        return;
    }
    setSceneRect (pixmap->rect ());
    qInfo () << "pixmap rect" << pixmap->rect ();
    this->resetTransform ();
    // this->centerOn (pixmapItem);
    // find out the maximum dimension of the pixmap
    int width = pixmap->size ().width ();
    int height = pixmap->size ().height ();
    int maxDim = (height > width) ? height : width;
    // find the minimum dimension of the view
    int minViewDim = (this->contentsRect ().size ().width ()
                      < this->contentsRect ().size ().height ())
                         ? this->contentsRect ().size ().width ()
                         : this->contentsRect ().size ().height ();
    // scale the view so the minimum dimension of the view is the same as the
    // maximum dimension of the pixmap
    this->scale
        (minViewDim / (double) maxDim
         , minViewDim / (double) maxDim);
}

void MinesweeperView::display ()
{
    emit requestBoard ();
}

void MinesweeperView::setBoardSize (QSize size)
{
    qInfo () << "changing size to" << size;
    this->size = size;
    if (pixmap != nullptr)
        delete pixmap;
    // initialize the pixmap and add it to the scene
    pixmap = new QPixmap (QSize (size.width () * TILE_SIZE
                               , size.height () * TILE_SIZE));
    pixmap->fill (Qt::red);
    pixmapItem->setPixmap (*pixmap);
    // zoom the view on the scene
    internalResize ();
    // emit requestBoard ();
}

void MinesweeperView::receiveBoard (const QSize &boardSize, const int *board, const Tile *covers)
{
    // if the size hasn't been initialized, exit this method
    if (nullptr == pixmap || size != boardSize)
        setBoardSize (boardSize);
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
            QPixmap *display = &coverImage;
            switch (covers[index])
            {
            case Tile::blank:
                // draw the number/bomb
                display = &numbers[board[index]];
                break;
            case Tile::covered:
                // the display variable is already set to cover so there's no
                // need to update that again here
                break;
            case Tile::flagged:
                display = &flagImage;
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
    Q_UNUSED (mines);
    qInfo () << "dead at" << where;
    enabled = false;
}

void MinesweeperView::won (QList<QPoint> mines)
{
    qInfo () << "won";
    for (const auto &mine : mines)
    {
        flagPlaced (mine, numFlags);
    }
    enabled = false;
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
    if (!enabled || nullptr == pixmap)
        return;
    qInfo () << "view flag placed" << point;
    this->numFlags = numFlags;
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.drawPixmap (translateFromMinesweeper(point), flagImage);
    pixmapItem->setPixmap (*pixmap);
}

void MinesweeperView::flagRemoved (QPoint point, int numFlags)
{
    if (!enabled || nullptr == pixmap)
        return;
    qInfo () << "view flag removed" << point;
    this->numFlags = numFlags;
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.drawPixmap (translateFromMinesweeper(point), coverImage);
    pixmapItem->setPixmap (*pixmap);
}

void MinesweeperView::lessonHighlightPlaced(QPoint point, int color)
{
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    if(color==2)
        {
        painter.drawPixmap (translateFromMinesweeper(point), redHighlight);
        }
    else if(color==3)
        {
            painter.drawPixmap (translateFromMinesweeper(point), orangeHighlight);
        }
    else if(color==4)
        {
            painter.drawPixmap (translateFromMinesweeper(point), yellowHighlight);
        }
    else if(color==5)
        {
            painter.drawPixmap (translateFromMinesweeper(point), pinkHighlight);
        }
    else if(color==6)
        {
            painter.drawPixmap (translateFromMinesweeper(point), blueHighlight);
        }
    else if(color==7)
        {
            painter.drawPixmap (translateFromMinesweeper(point), purpleHighlight);
        }
    else if(color==8)
        {
            painter.drawPixmap (translateFromMinesweeper(point), brownHighlight);
        }
    else if(color==9)
        {
            painter.drawPixmap (translateFromMinesweeper(point), blackHighlight);
        }
    pixmapItem->setPixmap (*pixmap);
}

void MinesweeperView::lessonHighlightRemoved(QPoint point)
{
    if (!enabled || nullptr == pixmap)
        return;
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.drawPixmap (translateFromMinesweeper(point), coverImage);
    pixmapItem->setPixmap (*pixmap);
}

void MinesweeperView::displayHighlight (QList<QPoint> coveredTiles)
{
    if (!enabled || nullptr == pixmap)
        return;
    QPainter painter (pixmap);
    painter.setBackgroundMode (Qt::TransparentMode);
    for (const auto &point : prevChord)
    {
        painter.drawPixmap (translateFromMinesweeper (point), coverImage);
    }
    for (const auto &point : coveredTiles)
    {
        painter.drawPixmap (translateFromMinesweeper (point), numbers[0]);
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

    if (!enabled)
        return;
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
        // highlight the covered tiles around this tile, showing the user
        // what will be cleared if there are enough flags around the point
        emit requestChord (minesweeperPos);
        break;
    default:
        break;
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

    if (!enabled)
        return;
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
    // reset the mouse button
    mouse = Qt::NoButton;
}

void MinesweeperView::resizeEvent (QResizeEvent* event)
{
    qInfo () << "New size" << event->size () << "old size" << event->oldSize () << "viewport size" << contentsRect () << "scene size" << mainScene->sceneRect ();
    event->accept ();
    internalResize ();
}

void MinesweeperView::clearCell (QPoint origin)
{
    if (!enabled)
        return;
    qInfo () << "view emitting clear" << origin << enabled;
    emit clear (origin);
}

void MinesweeperView::flagCell (QPoint origin)
{
    if (!enabled)
        return;
    qInfo () << "view emitting flag" << origin << enabled;
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

void MinesweeperView::makeConnections (Minefield &mines)
{
    // Connections for the minesweeper board
    connect (&mines, &Minefield::updateBoard
            , this, &MinesweeperView::receiveBoard);
    connect (this, &MinesweeperView::requestBoard
            , &mines, &Minefield::requestBoard);
    connect (this, &MinesweeperView::clear, &mines, &Minefield::clear);
    connect (this, &MinesweeperView::flag,  &mines, &Minefield::flag);
    connect (this, &MinesweeperView::chord, &mines, &Minefield::chord);
    connect (&mines, &Minefield::flagPlaced
            , this, &MinesweeperView::flagPlaced);
    connect (&mines, &Minefield::flagRemoved
            , this, &MinesweeperView::flagRemoved);
    connect (&mines, &Minefield::lessonHighlightPlaced, this,
            &MinesweeperView::lessonHighlightPlaced);
    connect (&mines, &Minefield::lessonHighlightRemoved, this,
            &MinesweeperView::lessonHighlightRemoved);
    connect (this, &MinesweeperView::requestChord
            , &mines, &Minefield::getSurroundings);
    connect (&mines, &Minefield::sendChord
            , this, &MinesweeperView::displayHighlight);
    connect (this, &MinesweeperView::requestIfCovered
            , &mines, &Minefield::getIfCovered);
    connect (&mines, &Minefield::sendCovered
            , this, &MinesweeperView::receiveIfCovered);
    connect (&mines, &Minefield::dead
            , this, &MinesweeperView::dead);
    connect (&mines, &Minefield::won
            , this, &MinesweeperView::won);
}

