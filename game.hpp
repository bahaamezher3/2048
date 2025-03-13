#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include <string>
#include <fstream> // For file operations

using namespace std;

class Game
{
private:
    Board board;
    bool gameOver;
    bool won;
    int highScore;

    void loadHighScore();
    void saveHighScore() const;

public:
    // Constructor to create a new ganme
    Game();

    // starting thr game
    void newGame();

    // doing a move for the given direction up down left right
    void processMove(char direction);

    // running the game
    void run();

    // Displaying the last status of the game
    void displayStatus() const;
};

#endif // GAME_HPP