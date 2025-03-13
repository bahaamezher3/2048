#include "game.hpp"
#include <ncurses.h>
#include <fstream>

using namespace std;

Game::Game() : gameOver(false), won(false), highScore(0)
{
    loadHighScore();
    newGame();
}

void Game::loadHighScore()
{
    ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
}

void Game::saveHighScore() const
{
    ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

void Game::newGame()
{
    board.reset();
    gameOver = false;
    won = false;
}

void Game::processMove(char direction)
{
    bool moved = false;

    board.saveState(); // Save state before making a move

    switch (direction)
    {
    case 'w': // Up
        moved = board.moveUp();
        break;
    case 's': // Down
        moved = board.moveDown();
        break;
    case 'a': // Left
        moved = board.moveLeft();
        break;
    case 'd': // Right
        moved = board.moveRight();
        break;
    default:
        cout << "Invalid move. Use W/A/S/D or arrow keys.\n";
        return;
    }

    // Add a new tile only if the move was valid
    if (moved)
    {
        board.addRandomTile();
        if (board.getScore() > highScore)
        {
            highScore = board.getScore();
            saveHighScore();
        }
    }

    // Check win/lose conditions
    if (board.hasWon() && !won)
    {
        won = true;
        cout << "\nCongratulations! You've reached 2048!\n";
        cout << "You can continue playing to get a higher score.\n";
    }

    if (!board.canMove())
    {
        gameOver = true;
    }
}

void Game::run()
{
    int ch;

    while (!gameOver)
    {
        // Display the current state
        displayStatus();

        // Get user input
        ch = getch();

        // Process the move
        switch (ch)
        {
        case KEY_UP:
            processMove('w');
            break;
        case KEY_DOWN:
            processMove('s');
            break;
        case KEY_LEFT:
            processMove('a');
            break;
        case KEY_RIGHT:
            processMove('d');
            break;
        case 'u': // Undo move
            board.undo();
            break;
        case 'q':
            printw("Quitting game...\n");
            gameOver = true;
            break;
        default:
            printw("Invalid move. Use arrow keys, U to undo, or Q to quit.\n");
            break;
        }
    }

    if (gameOver)
    {
        displayStatus();
        printw("Game Over! No more moves possible.\n");
        printw("Final Score: %d\n", board.getScore());
        printw("High Score: %d\n", highScore);
    }
}

void Game::displayStatus() const
{
    clear(); // Clear the screen
    printw("==== 2048 Game ====\n");
    board.display();
    printw("Controls: Arrow keys to move, U to undo, Q to quit\n");
    printw("High Score: %d\n", highScore);
}