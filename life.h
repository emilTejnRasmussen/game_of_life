#ifndef LIFE_H
#define LIFE_H

#include <stdbool.h>

#define ROWS 20
#define COLS 20

typedef struct {
    bool cells[ROWS][COLS];
} GameOfLife;

void next_generation(GameOfLife *game);

void life_seed_random(GameOfLife *game, int alive_percentage); 

#endif

