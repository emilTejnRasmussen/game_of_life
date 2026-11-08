#include "terminal.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define ALIVE "🟩"
#define DEAD "⬛"

void terminal_init()
{
    SetConsoleOutputCP(CP_UTF8);
}

void terminal_clear(void)
{
    printf("\033[2J\033[H");
}

void terminal_render(const GameOfLife *game)
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fputs(game->cells[i][j] ? ALIVE : DEAD, stdout);
        }
        putchar('\n');
    }

    fflush(stdout);
}

int terminal_read_key()
{
    if (_kbhit()) {
        int key = _getch();
        return key;
    }

    return -1;
}
