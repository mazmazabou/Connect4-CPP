# Connect 4 Game in C++

This is a command-line implementation of the classic Connect 4 game written in C++. The game supports different modes based on the number of players:

- **0P**: AI vs. AI (Random vs. User AI)
- **1P**: Human vs. AI
- **2P**: Human vs. Human
- **Test**: Random vs. Random for testing purposes

## How to Compile and Run

**Prerequisites:**

- A C++ compiler (e.g., `g++`)
- A terminal or command prompt

**Compilation:**

Open your terminal and navigate to the project directory. Compile the game using the following command:

```bash
g++ -o Connect4 connect4.cpp c4lib.cpp

## How to Run the Game

Run the executable with the following syntax:

./Connect4 [rows] [columns] [mode]

[rows]: Number of rows in the game board (e.g., 6)
[columns]: Number of columns in the game board (e.g., 7)
[mode]: Game mode (2P, 1P, 0P, or test)

Game Modes Explained
2P: Two human players play against each other.
1P: Human player vs. AI.
0P: AI vs. AI (Random vs. User AI).
test: AI vs. AI (Random vs. Random) for testing.

Gameplay
Simply enter the index of the column you would like to place your piece. 0 is the first column and ([column you input] - 1) is the last column.
