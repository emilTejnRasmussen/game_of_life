#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "life.h"
#include "terminal.h"

#define ALIVE_PERCENTAGE 30

int main(void) {
    GameOfLife game = {0};

    srand((unsigned int)time(NULL));
    life_seed_random(&game, ALIVE_PERCENTAGE);

    int generation = 0;
    bool running = true;
    bool paused = false;
    bool needs_render = true;

    terminal_init();
    terminal_clear();

    DWORD64 generation_interval_ms = 500; // ms to update simulation
    DWORD64 last_update = GetTickCount64();

    const DWORD64 min_interval_ms = 25;
    const DWORD64 max_interval_ms = 2500;
    const DWORD64 speed_step_ms = 25;

    while (running) {
        int key = terminal_read_key();

        switch (key) {
        case 'Q':
        case 'q':
            running = false;
            break;

        case ' ':
            paused = !paused;
            needs_render = true;

            if (!paused) {
                last_update = GetTickCount64();
            }

            break;

        case 'N':
        case 'n':
            if (paused) {
                next_generation(&game);
                generation++;
                needs_render = true;
            }
            break;

        case '+':
            if (generation_interval_ms > min_interval_ms) {
                generation_interval_ms -= speed_step_ms;
                needs_render = true;
            }
            break;

        case '-':
            if (generation_interval_ms < max_interval_ms) {
                generation_interval_ms += speed_step_ms;
                needs_render = true;
            }
            break;

        case 'R':
        case 'r':
            life_seed_random(&game, ALIVE_PERCENTAGE);
            generation = 0;
            last_update = GetTickCount64();
            needs_render = true;
            break;
        }

        if (!running)
            break;

        DWORD64 now = GetTickCount64();
        DWORD64 time_passed = now - last_update;

        if (!paused && time_passed >= generation_interval_ms) {
            next_generation(&game);
            generation++;

            needs_render = true;
            last_update = now;
        }

        if (needs_render) {
            terminal_render_frame(&game, generation, generation_interval_ms, paused);
            needs_render = false;
        }

        Sleep(10);
    }

    terminal_cleanup();

    return EXIT_SUCCESS;
}
