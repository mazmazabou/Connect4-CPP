#include "c4lib.h"
#include <iostream>
using namespace std;

/**
 * @brief returns the smallest y coordinate that is BLANK in
 *        column x or -1 if no location is BLANK
 */
int findYValue(BoardValue** board, int ydim, int x);

// ------------------------------------------------------------

// converts integer player value: 0 or 1 to appropriate enum
enum BoardValue playerToValue[2] = {RED, YELLOW};

// ----------------------------------------------------------------------

// Helper function
int findYValue(BoardValue** board, int ydim, int x)
{
    for (int i = 0; i < ydim ; i++) {
        if (board[i][x] ==  BLANK) {
            return i;
        }
    }
    return -1;
}

BoardValue** allocateBoard(int ydim, int xdim)
{
    BoardValue** board = new BoardValue*[ydim]; //allocate memory for rows

    for (int i = 0; i < ydim; i++) {
        board[i] = new BoardValue[xdim]; // allocate memory for column of row
        for (int j = 0; j < xdim; j++) {
            board[i][j] = BLANK;
        }
    }
    return board;
}

void deallocateBoard(BoardValue** board, int ydim)
{
    if (board != nullptr) {
        for (int i = 0; i < ydim; i++) {
            if (board[i] != nullptr) {
                delete[] board[i];
            }
        }
        delete[] board;
    }
}

void printBoard(BoardValue** board, int ydim, int xdim)
{
    const char* boardToString[] = { "\U000026ab", "\U0001F534", "\U0001F7E1" };
                                            //  "⚫",          "🔴",         "🟡"}
    for(int y = ydim-1; y >= 0; y--){
        for(int x = 0; x < xdim; x++) {
            cout << boardToString[(int)board[y][x]] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool getNextHumanInput(
        BoardValue** board,
        int ydim, int xdim,
        int *y, int *x,
        int currentPlayer)
{
    cout << "Enter the location: " << endl;
    cin >> *x;

    if (*x >= xdim || *x < 0) {
        cout << "Early exit" << endl;
        return true; // input error
    }

    *y = findYValue(board, ydim, *x);

    if (*y == -1) {
        cout << "Early exit" << endl;
        return true; // input error
    }

    board[*y][*x] = playerToValue[currentPlayer];
    return false; // successfully placed piece
}

bool hasWon(
        BoardValue** board,
        int ydim, int xdim,
        int sy, int sx,
        int currentPlayer)
{
    const int NDIRS = 4; //num of directions
    const int xDirDelta[NDIRS] = { 0, +1, -1, +1}; //delta x for all 4 directions
    const int yDirDelta[NDIRS] = {+1,  0, +1, +1}; //delta y for all 4 directions

    /*
    delta
    {x,y}
    {0,1} 1 up
    {1,0} 1 right
    {-1,1} 1 left 1 up (diagonal left)
    {1,1} 1 right 1 up (diagonal right)
    */

    const int winningCount = 4;
    BoardValue playerPiece = playerToValue[currentPlayer];

    //check adding the elements of the delta array
    for (int dir = 0; dir < NDIRS; dir++) { //0 >
        int count = 1;

        // positive directions
        for (int i = 1; i < winningCount; i++) { //
            int nx = sx + (i * xDirDelta[dir]); //ex. sx = 1, i = 3, xDirDelta[0] = +1
            // nx = 4 , farthest x to check from
            // entry x = 1 is x = 4
            int ny = sy + (i * yDirDelta[dir]); // same for sy -> ny

            if (nx >= 0 && nx < xdim && ny >= 0 && ny < ydim && board[ny][nx] == playerPiece) {

                count++; //if nx is not out of our dimensions and it is the piece the player reaches
                // after successfully iterating through the loop then we add it to count

                if (count == winningCount) {
                    return true;
                }
                //if count is 4 -> player wins
            }
            else break;
        }

        //check subtracting the elements of the delta array
        for (int i = 1; i < winningCount; i++) {
            int nx = sx - (i * xDirDelta[dir]);
            int ny = sy - (i * yDirDelta[dir]);

            if (nx < xdim && nx >= 0 && ny < ydim && ny >= 0 && board[ny][nx] == playerPiece) {
                count++;
                if (count == winningCount) {
                    return true;
                }
            } else break;
        }
    }

    return false; // no win found
}

bool isDraw(
        BoardValue** board,
        int ydim, int xdim)
{
    for (int i = 0; i < ydim; i++) {
        for (int j = 0; j < xdim; j++) {
            if (board[i][j] == BLANK) {
                return false; // we found an empty spot
            }
        }
    }
    return true; // the board is full
}

bool getUserAIInput(BoardValue** board, int ydim, int xdim, int *y, int *x, int currentPlayer) {

    BoardValue currentPlayerPiece = playerToValue[currentPlayer];
    BoardValue opponentPiece = (currentPlayerPiece == RED) ? YELLOW : RED; // Determine the opponent's piece
                                                                           // opponent piece evaluates to yellow when
                                                                           // current player piece is red
    // First priority: block opponent from winning
    for (int j = 0; j < xdim; j++) {
        int possibleY = findYValue(board, ydim, j);
        if (possibleY != -1) { // Found a valid spot , findYvalue evaluates to not false
            // Simulate opponent's move
            board[possibleY][j] = opponentPiece;
            if (hasWon(board, ydim, xdim, possibleY, j, 1 - currentPlayer)) {
                board[possibleY][j] = BLANK; // Undo the move
                *y = possibleY;
                *x = j;
                board[possibleY][j] = currentPlayerPiece; // Block the opponent
                return false; // Move made
            }
            board[possibleY][j] = BLANK; // Undo the move if it doesn't block the opponent
        }
    }

    // Second priority: Try to find the best move for the current player (myAI)
    for (int j = 0; j < xdim; j++) {
        int possibleY = findYValue(board, ydim, j);
        if (possibleY != -1) { // Found a valid spot
            // temp place opponent's piece to see if it results in their win
            board[possibleY][j] = opponentPiece;
            if (hasWon(board, ydim, xdim, possibleY, j, 1 - currentPlayer)) { // Check if opponent would win
                board[possibleY][j] = currentPlayerPiece; // block win by placing current player's piece
                *y = possibleY;
                *x = j;
                return false; // made a blocking move
            } else {
                // undo move if it doesn't block opponent from winning
                board[possibleY][j] = BLANK;
            }
        }
    }

    // Fallback option
    for (int j = 0; j < xdim; j++) {
        int possibleY = findYValue(board, ydim, j);
        if (possibleY != -1) { // Found valid spot
            *y = possibleY;
            *x = j;
            board[possibleY][j] = currentPlayerPiece; // Make move
            return false; // Move made
        }
    }

    return true; // If the loop completes without finding a spot no move was made
}


bool getRandomAIInput(
        BoardValue** board,
        int ydim, int xdim,
        int *y, int *x,
        int currentPlayer)
{
    // Allocate variable size array (we don't know xdim when we compile)
    int* possible = new int[xdim];
    int numX = 0;
    bool error = true;
    // find all the possible columns with a blank
    for(int i = 0; i < xdim; i++){
        if(board[ydim-1][i] == BLANK){
            possible[numX++] = i;
        }
    }
    // If at least 1 column has a blank
    if(numX != 0){
        // Choose one column
        *x = possible[rand()%numX];
        *y = findYValue(board, ydim, *x);
        board[*y][*x] = playerToValue[currentPlayer];
        error = false;
    }
    delete [] possible;
    return error;
}