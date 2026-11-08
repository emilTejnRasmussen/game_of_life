#ifndef TERMINAL_H
#define TERMINAL_H

#include "life.h"
#include <basetsd.h>

void terminal_init(void);

void terminal_clear(void);

void terminal_home(void);

void terminal_render_frame(
        const GameOfLife *game, 
        int generation,
        DWORD64 interval_ms, 
        bool paused
);

int terminal_read_key(void);

void terminal_cleanup(void);

#endif
