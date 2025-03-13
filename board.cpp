#include "board.hpp"
#include <ncurses.h>

using namespace std;

Board::Board() : score(0)
{
    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize board
    reset();
}

void Board::reset()
{
    // Create a 4x4 grid with all cells initialized to 0
    grid = vector<vector<int>>(SIZE, vector<int>(SIZE, 0));
    score = 0;

    // Add two random tiles to start
    addRandomTile();
    addRandomTile();

    while (!history.empty())
        history.pop(); // Clear history on reset
}

void Board::addRandomTile()
{
    // Find all empty cells
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (grid[i][j] == 0)
            {
                emptyCells.push_back({i, j});
            }
        }
    }

    // If there are no empty cells, return
    if (emptyCells.empty())
    {
        return;
    }

    // Choose a random empty cell
    int index = rand() % emptyCells.size();
    int row = emptyCells[index].first;
    int col = emptyCells[index].second;

    // Add a new tile (90% chance for 2, 10% chance for 4)
    grid[row][col] = (rand() % 10 == 0) ? 4 : 2;
}

bool Board::moveLeft()
{
    bool moved = false;

    for (int row = 0; row < SIZE; ++row)
    {
        // Slide all non-zero tiles to the left
        for (int col = 1; col < SIZE; ++col)
        {
            if (grid[row][col] != 0)
            {
                int target = col;
                while (target > 0 && grid[row][target - 1] == 0)
                {
                    target--;
                }

                if (target != col)
                {
                    grid[row][target] = grid[row][col];
                    grid[row][col] = 0;
                    moved = true;
                }
            }
        }

        // Merge tiles with the same value
        for (int col = 0; col < SIZE - 1; ++col)
        {
            if (grid[row][col] != 0 && grid[row][col] == grid[row][col + 1])
            {
                grid[row][col] *= 2;
                grid[row][col + 1] = 0;
                score += grid[row][col];
                moved = true;

                // Slide again to fill gaps
                for (int j = col + 2; j < SIZE; ++j)
                {
                    if (grid[row][j] != 0)
                    {
                        grid[row][j - 1] = grid[row][j];
                        grid[row][j] = 0;
                    }
                }
            }
        }
    }

    return moved;
}

// Implement other movement methods similarly
bool Board::moveRight()
{
    // Code will be similar to moveLeft but in reverse direction
    bool moved = false;

    for (int row = 0; row < SIZE; ++row)
    {
        // Slide all non-zero tiles to the right
        for (int col = SIZE - 2; col >= 0; --col)
        {
            if (grid[row][col] != 0)
            {
                int target = col;
                while (target < SIZE - 1 && grid[row][target + 1] == 0)
                {
                    target++;
                }

                if (target != col)
                {
                    grid[row][target] = grid[row][col];
                    grid[row][col] = 0;
                    moved = true;
                }
            }
        }

        // Merge tiles with the same value
        for (int col = SIZE - 1; col > 0; --col)
        {
            if (grid[row][col] != 0 && grid[row][col] == grid[row][col - 1])
            {
                grid[row][col] *= 2;
                grid[row][col - 1] = 0;
                score += grid[row][col];
                moved = true;

                // Slide again to fill gaps
                for (int j = col - 2; j >= 0; --j)
                {
                    if (grid[row][j] != 0)
                    {
                        grid[row][j + 1] = grid[row][j];
                        grid[row][j] = 0;
                    }
                }
            }
        }
    }

    return moved;
}

bool Board::moveUp()
{
    bool moved = false;

    for (int col = 0; col < SIZE; ++col)
    {
        // Slide all non-zero tiles upward
        for (int row = 1; row < SIZE; ++row)
        {
            if (grid[row][col] != 0)
            {
                int target = row;
                while (target > 0 && grid[target - 1][col] == 0)
                {
                    target--;
                }

                if (target != row)
                {
                    grid[target][col] = grid[row][col];
                    grid[row][col] = 0;
                    moved = true;
                }
            }
        }

        // Merge tiles with the same value
        for (int row = 0; row < SIZE - 1; ++row)
        {
            if (grid[row][col] != 0 && grid[row][col] == grid[row + 1][col])
            {
                grid[row][col] *= 2;
                grid[row + 1][col] = 0;
                score += grid[row][col];
                moved = true;

                // Slide again to fill gaps
                for (int i = row + 2; i < SIZE; ++i)
                {
                    if (grid[i][col] != 0)
                    {
                        grid[i - 1][col] = grid[i][col];
                        grid[i][col] = 0;
                    }
                }
            }
        }
    }

    return moved;
}

bool Board::moveDown()
{
    bool moved = false;

    for (int col = 0; col < SIZE; ++col)
    {
        // Slide all non-zero tiles downward
        for (int row = SIZE - 2; row >= 0; --row)
        {
            if (grid[row][col] != 0)
            {
                int target = row;
                while (target < SIZE - 1 && grid[target + 1][col] == 0)
                {
                    target++;
                }

                if (target != row)
                {
                    grid[target][col] = grid[row][col];
                    grid[row][col] = 0;
                    moved = true;
                }
            }
        }

        // Merge tiles with the same value
        for (int row = SIZE - 1; row > 0; --row)
        {
            if (grid[row][col] != 0 && grid[row][col] == grid[row - 1][col])
            {
                grid[row][col] *= 2;
                grid[row - 1][col] = 0;
                score += grid[row][col];
                moved = true;

                // Slide again to fill gaps
                for (int i = row - 2; i >= 0; --i)
                {
                    if (grid[i][col] != 0)
                    {
                        grid[i + 1][col] = grid[i][col];
                        grid[i][col] = 0;
                    }
                }
            }
        }
    }

    return moved;
}

bool Board::isGameOver() const
{
    // Check if the board is full
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (grid[i][j] == 0)
            {
                return false; // There's an empty cell, game is not over
            }
        }
    }

    // Check if there are any possible merges
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            if (grid[i][j] == grid[i][j + 1])
            {
                return false; // There's a possible horizontal merge
            }
        }
    }

    for (int j = 0; j < SIZE; ++j)
    {
        for (int i = 0; i < SIZE - 1; ++i)
        {
            if (grid[i][j] == grid[i + 1][j])
            {
                return false; // There's a possible vertical merge
            }
        }
    }

    return true; // No empty cells and no possible merges
}

bool Board::hasWon() const
{
    // Check if any tile has reached 2048
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (grid[i][j] >= 2048)
            {
                return true;
            }
        }
    }
    return false;
}

int Board::getScore() const
{
    return score;
}

void Board::display() const
{
    printw("\nScore: %d\n\n", score);

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (grid[i][j] == 0)
            {
                printw(".    ");
            }
            else
            {
                printw("%d", grid[i][j]);
                // Add spacing based on number of digits
                int digits = 0;
                int temp = grid[i][j];
                while (temp > 0)
                {
                    temp /= 10;
                    digits++;
                }
                for (int k = 0; k < 5 - digits; ++k)
                {
                    printw(" ");
                }
            }
        }
        printw("\n\n");
    }
}

bool Board::canMove() const
{
    // Check for empty cells
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (grid[i][j] == 0)
            {
                return true;
            }
        }
    }

    // Check for adjacent tiles with the same value
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            if (grid[i][j] == grid[i][j + 1])
            {
                return true;
            }
        }
    }

    for (int j = 0; j < SIZE; ++j)
    {
        for (int i = 0; i < SIZE - 1; ++i)
        {
            if (grid[i][j] == grid[i + 1][j])
            {
                return true;
            }
        }
    }

    return false;
}

void Board::saveState()
{
    history.push({grid, score});
}

void Board::undo()
{
    if (!history.empty())
    {
        auto previousState = history.top();
        history.pop();
        grid = previousState.first;
        score = previousState.second;
    }
}