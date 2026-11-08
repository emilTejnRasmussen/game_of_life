#include "life.h"

#include <string.h>

static int count_neighbors(bool grid[ROWS][COLS], int row, int col);


void next_generation(GameOfLife *game) {
    bool temp_grid[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = count_neighbors(game->cells, i, j);
            if (game->cells[i][j] && (neighbors == 2 || neighbors == 3)) {
                temp_grid[i][j] = true;
            } else if (!game->cells[i][j] && neighbors == 3) {
                temp_grid[i][j] = true;
            } else {
                temp_grid[i][j] = false;
            }
        }
    }

    memcpy(game->cells, temp_grid, sizeof(temp_grid));
}

static int count_neighbors(bool grid[ROWS][COLS], int row, int col) {
    int neighbors = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;

            int calcRow = row + i;
            int calcCol = col + j;

            if (calcRow < 0 || calcRow >= ROWS)
                continue;
            if (calcCol < 0 || calcCol >= COLS)
                continue;

            if (grid[calcRow][calcCol])
                neighbors++;
        }
    }

    return neighbors;
}

