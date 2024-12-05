#ifndef C4LIB_H
#define C4LIB_H


/**
 * @brief An enumerated type to make the code more readable
 *  as we represent the status of each board location:
 *   BLANK=0, RED=1, YELLOW=2
 */
enum BoardValue { BLANK=0, RED, YELLOW };

/**
 * @brief Allocate the 2D BoardValue array with
 *        ydim rows and xdim columns
 */
BoardValue** allocateBoard(int ydim, int xdim);

/**
 * @brief Deallocate the 2D BoardValue array with
 *        ydim rows
 */
void deallocateBoard(BoardValue** board, int ydim);

/**
 * @brief Prints the board using Unicode emojis for
 *   the blank, red, and yellow pieces.
 *
 */
void printBoard(BoardValue** board, int ydim, int xdim);


/**
 * @brief Checks if the current player has won by having
 *        4 consecutive markers in a row (diagonal, vertical, horizontal)
 *
 * @param [in] board  2D array of board values
 * @param [in] ydim number of rows
 * @param [in] xdim number of columns
 * @param [in] sy row (y-coordinate) where the player just added their piece
 * @param [in] sx col (x-coordinate) where the player just added their piece
 * @param [in] currentPlayer (0 = red, 1 = yellow)
 * @return true if the player has won
 * @return false if the player has NOT won
 */
bool hasWon(
        BoardValue** board,
        int ydim, int xdim,
        int sy, int sx,
        int currentPlayer);

/**
 * @brief Checks if the game is over via a draw (i.e. the board
 *  is full)
 *
 * @param [in] board  2D array of voard values
 * @param [in] ydim number of rows
 * @param [in] xdim number of columns
 * @return true if all places are full with a red or yellow piece
 * @return false if there is still a blank location
 */
bool isDraw(
        BoardValue** board,
        int ydim, int xdim);



/**
 * @brief Get the Next Human Input choice let's the user specify
 * the columns where they will drop their piece and then finds
 * the appropriate row where the piece will land and sets the
 * BoardValue entry in the 2D board array, appropriately.
 *
 * @param [inout] board  2D array of voard values
 * @param [in] ydim number of rows
 * @param [in] xdim number of columns
 * @param [out] y pointer to an integer that should be set with the input row
 * @param [out] x pointer to an integer that should be set with the input column
 * @param [in] currentPlayer 0 = red, 1 = yellow
 * @return true If there is an error in the user's input such as
 *  selecting a place that is not BLANK or out of bounds
 * @return false If the user successfully chose a location.
 */
bool getNextHumanInput(
        BoardValue** board,
        int ydim, int xdim,
        int *y, int *x,
        int currentPlayer);

/**
 * @brief AI that will be the second player when we are in 1P or 0P mode
 *
 * @param [inout] board  2D array of voard values
 * @param [in] ydim number of rows
 * @param [in] xdim number of columns
 * @param [out] y pointer to an integer that should be set with the chosen row
 * @param [out] x pointer to an integer that should be set with the chosen column
 * @param [in] currentPlayer 0 = red, 1 = yellow
 * @return true If there is an error (i.e. no possible place to play exists)
 * @return false If a location was succesfully chosen.
 */
bool getUserAIInput(
        BoardValue** board,
        int ydim, int xdim,
        int *y, int *x,
        int currentPlayer);


/**
 * @brief AI that will be the first player when we are in 0P mode
 *
 * @param [inout] board  2D array of voard values
 * @param [in] ydim number of rows
 * @param [in] xdim number of columns
 * @param [out] y pointer to an integer that should be set with the chosen row
 * @param [out] x pointer to an integer that should be set with the chosen column
 * @param [in] currentPlayer 0 = red, 1 = yellow
 * @return true If there is an error (i.e. no possible place to play exists)
 * @return false If a location was succesfully chosen.
 */
bool getRandomAIInput(
        BoardValue** board,
        int ydim, int xdim,
        int *y, int *x,
        int currentPlayer);

// --------------------------------------------------------------------------
// You can add prototypes if you want to define other functions in c4lib.cpp
// that you'd like to call in connect4.cpp


#endif