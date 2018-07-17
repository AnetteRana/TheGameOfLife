#include <QtGui>
#include "rasterwindow.h"

#include <iostream>
#include <time.h> // random

#include <unistd.h> // sleep (delay)

using namespace std;

// initialize variables and functions
int length = 14;
int windowSize = 500;

int squareSize = 6;
int squareHalfSize = (squareSize/2);

int myIterator = 0;

bool *board0 = new bool[length*length]{false};
bool *board1 = new bool[length*length]{false};

void runLifeMain();
void OLDdrawBoard(bool *in);
void iterateBoard(bool *oldBoard, bool *newBoard);


//////////////////////////////////////////////////////////////////////

class GreatWindow : public RasterWindow
{
public:
    GreatWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;

private:
    int m_timerId;
};

GreatWindow::GreatWindow()
{
    setTitle("This is a great window");
    resize(windowSize, windowSize);

    m_timerId = startTimer(1000);

    // initialize pattern ?
    for (int i = 0; i < (length*length); i++)
    {

        if ((i > length)&&(i < length*2))
        {
            board0[i] = true;
        }
    }
}

void GreatWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
        renderLater();
}

//////////////////////////////////////////////////////////////////////
// this is what happens each render
void GreatWindow::render(QPainter *p)
{
    static const QPoint mySquare[4] = {
        QPoint(squareHalfSize, squareHalfSize),
        QPoint(-squareHalfSize, squareHalfSize),
        QPoint(-squareHalfSize, -squareHalfSize),
        QPoint(squareHalfSize, -squareHalfSize)
    };

    QColor aliveColor(255, 0, 0);
    QColor deadColor(0, 0, 0, 100);

    p->setRenderHint(QPainter::Antialiasing);
    p->translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    p->setPen(Qt::NoPen);
    //p->setBrush(aliveColor);

    //QTime time = QTime::currentTime();



    /////* draw all the squares *

    // first go to bottom left corner
    p->translate(-length*squareSize, -length*squareSize);




    // then draw them all
    int squareNumber = 0;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            p->translate((squareSize+1), 0);

            if (myIterator%2)
            {
                if (board1[squareNumber])
                {
                    p->setBrush(aliveColor);
                    p->drawConvexPolygon(mySquare, 4);
                }
                else
                {
                    p->setBrush(deadColor);
                    p->drawConvexPolygon(mySquare, 4);
                }
            }
            else
            {
                if (board0[squareNumber])
                {
                    p->setBrush(aliveColor);
                    p->drawConvexPolygon(mySquare, 4);
                }
                else
                {
                    p->setBrush(deadColor);
                    p->drawConvexPolygon(mySquare, 4);
                }
            }
            squareNumber++;
        }
        p->translate(-(squareSize+1)*length, (squareSize+1));
    }




    // run algorithm
    if (myIterator%2)    {iterateBoard(board1, board0);}
    else        {iterateBoard(board0, board1);}
    myIterator++;

}

//////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    GreatWindow myWindow;
    myWindow.show();

    //    AnalogClockWindow clock;
    //    clock.show();

    return app.exec();
}

void iterateBoard (bool *oldBoard, bool *newBoard)
{
    // iterate whole board, each place being current in turn
    // test oldBoard, change newBoard
    for (int current = 0; current < (length*length); current++)
    {
        // do individual test to see if alive
        // find how many alive in the 8 around
        int alive = 0;

        //if not on top line
        if (!(current-length<0))
        {
            // 0
            if (!(current%length ==0)) // if not on left
            {
                if (oldBoard[current-(length+1)])
                    alive++;
            }
            // 1
            if (oldBoard[current-length])
                alive++;
            // 2
            if (!((current+1)%length == 0)) // if not on right
            {
                if (oldBoard[current-(length-1)])
                    alive++;
            }
        }

        // 3
        if (!(current%length) ==0) // if not on left
        {
            if (oldBoard[current-1])
                alive++;
        }
        // 5
        if (!((current+1)%length == 0)) // if not on right
        {
            if (oldBoard[current+1])
                alive++;
        }

        //if not on bottom line
        if (current+length < (length*length))
        {
            // 6
            if (!(current%length ==0)) // if not on left
            {
                if (oldBoard[current+(length-1)])
                    alive++;
            }
            // 7
            if (oldBoard[current+length])
                alive++;
            // 8
            if (((current+1)%length) != 0) // if not on right
            {
                if (oldBoard[current+(length+1)])
                    alive++;
            }
        }


        // now you have counted the alive around
        if (oldBoard[current]) // is alive
        {
            if (alive == 2)
            {
                newBoard[current] = true;
            }
            else if (alive ==3)
            {
                newBoard[current] = true;
            }
            else
            {
                newBoard[current] = false;
            }
        }
        else // is dead
        {
            if (alive == 3)
            {
                newBoard[current] = true;
            }
            else
            {
                newBoard[current] = false;
            }
        }
    }
}
