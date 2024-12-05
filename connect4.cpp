#include <iostream>
#include <iomanip>
#include <cstring>
#include "c4lib.h"
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 4){
        cout << "Please provide the board dimensions, either 0P|1P|2P, and an optional seed" << endl;
        return 1;
    }
    int ydim, xdim, seed;
    BoardValue** board = NULL;

    // code to convert the command line arguments to set the value ydim and xdim
    ydim = atoi(argv[1]);
    xdim = atoi(argv[2]);

    // Since the seed is optional we need to check if there is another argument
    if(argc >= 5){
        // set the seed with the integer value from the command line
        seed = atoi(argv[4]);
    }
    else {
        // if no seed was provided we'll use the current time
        seed = time(0);
    }
    srand(seed);


    // Determine player modes
    int numP = 2;
    if(strcmp(argv[3],"1P") == 0 || strcmp(argv[3], "1p") == 0){
        numP = 1;
    }
    else if(strcmp(argv[3],"0P") == 0 || strcmp(argv[3], "0p") == 0){
        numP = 0;
    }
    else if(strcmp(argv[3],"test") == 0){
        numP = -1;
    }
    cout << "Num players: " << numP << endl;

    // Initialization code
    bool win = false, tie = false;
    board = allocateBoard(ydim, xdim);

    int turn = 0;        // Number of turns for the game
    int player = 0;      // MUST alternate between 0 (red) and 1 (yellow)
    // to represent the two players
    bool error = false;  // input error?
    while(!error && !win && !tie){
        // ------------------------------------------------------------

        // Increment the turn and print the board
        turn++;
        printBoard(board, ydim, xdim);
        // Get the input, check for errors, a winner or a draw
        int x, y;
        if(numP == -1) {
            // Random vs. Random
            error = getRandomAIInput(board, ydim, xdim, &y, &x, player);
        }
        else if(numP == 0 && player == 0){
            // Random vs. User AI
            error = getRandomAIInput(board, ydim, xdim, &y, &x, player);
        }
        else if( (numP == 0 || numP == 1) && player == 1 ){
            // Random vs. User AI ..or.. Human vs. User AI
            error = getUserAIInput(board, ydim, xdim, &y, &x, player);
        }
        else {
            // Human vs. user AI ..or.. Human vs. Human
            error = getNextHumanInput(board, ydim, xdim, &y, &x, player);
        }
        // ------------------------------------------------------------

        // code to deal with errors and determine if there is a winner or a draw.
        // Then change to the next player and repeat

        // check for win or tie
        win = hasWon(board, ydim, xdim, y, x, player);
        tie = isDraw(board, ydim, xdim);

        // Be sure to switch the player

        if(!win && !tie && !error) {
            player = 1 - player;
        }
    }

    //  This code will output result of game
    printBoard(board, ydim, xdim);

    if(win == true && player == 1) {
        cout << "Yellow wins" <<  endl;
    }

    else if(win == true && player == 0) {
        cout <<  "Red wins" <<  endl;
    }

    else if(tie) {
        cout <<  "Draw" <<  endl;
    }

    else if(error) {
        cout <<  "Early exit" <<  endl;
    }


    cout <<  "Last turn " << turn <<  endl;

    deallocateBoard(board, ydim);

    return 0;
}