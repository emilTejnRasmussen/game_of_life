#include "terminal.h"
#include <stdio.h>

#define ALIVE '#'
#define DEAD '.'

void terminal_clear(void)
{
    printf("\033[H\033[2J");
}

void terminal_render(const GameOfLife *game)
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            putchar(game->cells[i][j] ? ALIVE : DEAD);
        }
        putchar('\n');
    }

    fflush(stdout);
}
