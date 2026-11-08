#ifndef LIFE_H
#define LIFE_H

#include <stdbool.h>

#define ROWS 20
#define COLS 40

typedef struct {
    bool cells[ROWS][COLS];
} GameOfLife;

void next_generation(GameOfLife *game);

#endif

