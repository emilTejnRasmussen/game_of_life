#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "life.h"

#define ALIVE '#'
#define DEAD '.'

void print_grid(bool grid[ROWS][COLS]);

int count_neighbors(bool grid[ROWS][COLS], int row, int col);

int main(void) {
    GameOfLife game = {0};

    game.cells[0][1] = true; 
    game.cells[1][2] = true;
    game.cells[2][0] = true;
    game.cells[2][1] = true;
    game.cells[2][2] = true;



    for (int gen = 0; gen < 10; gen++) {
        printf("\033[H\033[2J");

        printf("Generation %d.\n", gen);
        print_grid(game.cells);
        fflush(stdout);

        Sleep(500);

        next_generation(&game);
    }

    return EXIT_SUCCESS;
}

void print_grid(bool grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            putchar(grid[i][j] ? ALIVE : DEAD);
        }
        putchar('\n');
    }
}
