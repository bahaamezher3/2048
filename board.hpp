#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack> // For undo functionality

using namespace std;

class Board
{
private:
    // Standard 2048 board is 4x4
    static const int SIZE = 4;
    vector<vector<int>> grid;
    int score;
    stack<pair<vector<vector<int>>, int>> history; // Stack to store previous states

public:
    // Constructor
    Board();

    // Reset the board
    void reset();

    // Add a new tile (2 or 4) to a random empty cell
    void addRandomTile();

    // Move tiles and merge same values
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    // Check if game is over (no valid moves left)
    bool isGameOver() const;

    // Check if 2048 tile exists (win condition)
    bool hasWon() const;

    // Get current score
    int getScore() const;

    // Display the board
    void display() const;

    // Check if there are valid moves
    bool canMove() const;

    // Save and restore state for undo functionality
    void saveState();
    void undo();
};

#endif // BOARD_HPP