#include <iostream>
#include <time.h> // random

#include <unistd.h> // sleep (delay)

using namespace std;

int length = 64;
int myIterator = 0;

bool *board0 = new bool[length*length]{false};
bool *board1 = new bool[length*length]{false};

void drawBoard(bool *in);
void iterateBoard(bool *oldBoard, bool *newBoard);

///////////////-------------------------------------//

int runLifeMain()
{
    //    // initialize something random
    //    for (int i = 0; i < (length*length); i++)
    //    {
    //        board0[i] = (rand() % 2 -1);
    //    }

    // initialize pattern ?
    for (int i = 0; i < (length*length); i++)
    {

        if ((i > length)&&(i < length*2))
        {
            board0[i] = true;
        }
    }

    // draw one of the arrays
    if (myIterator%2)    {drawBoard(board1);}
    else        {drawBoard(board0);}

    // run algorithm
    if (myIterator%2)    {iterateBoard(board1, board0);}
    else        {iterateBoard(board0, board1);}

    myIterator++;




    return 0;
}

void drawBoard (bool *in)
{
    cout << "\n\n\n";

    for (int i = 0; i < (length*length); i++)
    {
        if (in[i])
        {
            cout << 'X';
        }
        else
        {
            cout << ' ';
        }

        if ((i+1)%length == 0)
        {
            cout << endl;
        }
    }
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
