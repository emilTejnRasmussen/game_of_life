#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ROWS 20
#define COLS 40
#define ALIVE '#'
#define DEAD '.'

void print_grid(bool grid[ROWS][COLS]);

int count_neighbors(bool grid[ROWS][COLS], int row, int col);

void next_generation(bool grid[ROWS][COLS]);

int main(void) {
    bool grid[ROWS][COLS] = {false};

    grid[0][1] = true;
    grid[1][2] = true;
    grid[2][0] = true;
    grid[2][1] = true;
    grid[2][2] = true;



    for (int gen = 0; gen < 10; gen++) {
        printf("\033[H\033[2J");

        printf("Generation %d.\n", gen);
        print_grid(grid);
        fflush(stdout);

        Sleep(500);

        next_generation(grid);
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

int count_neighbors(bool grid[ROWS][COLS], int row, int col) {
    int neighbors = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;

            int calcRow = row + i;
            int calcCol = col + j;

            if (!(calcRow >= 0 && calcRow < ROWS))
                continue;
            if (!(calcCol >= 0 && calcCol < COLS))
                continue;

            if (grid[calcRow][calcCol])
                neighbors++;
        }
    }

    return neighbors;
}

void next_generation(bool grid[ROWS][COLS]) {
    bool temp_grid[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = count_neighbors(grid, i, j);
            if (grid[i][j] && (neighbors == 2 || neighbors == 3)) {
                temp_grid[i][j] = true;
            } else if (!grid[i][j] && neighbors == 3) {
                temp_grid[i][j] = true;
            } else {
                temp_grid[i][j] = false;
            }
        }
    }

    memcpy(grid, temp_grid, sizeof(temp_grid));
}
