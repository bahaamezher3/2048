#include "game.hpp"
#include <ncurses.h>

int main()
{
    initscr();            // Initialize the window
    cbreak();             // Disable line buffering
    noecho();             // Don't echo while we do getch
    keypad(stdscr, TRUE); // Enable function keys

    printw("Welcome to 2048!\n");
    printw("Use arrow keys to move tiles, Q to quit.\n");
    printw("Press any key to start...\n");
    getch(); // Wait for user input

    Game game;
    game.run();

    endwin();

    return 0;
}