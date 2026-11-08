#ifndef TERMINAL_H
#define TERMINAL_H

#include "life.h"

void terminal_init(void);

void terminal_clear(void);

void terminal_render(const GameOfLife *game);

int terminal_read_key(void);

#endif
