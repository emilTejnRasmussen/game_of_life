#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "life.h"
#include "terminal.h"

int main(void) {
    GameOfLife game = {0};

    game.cells[0][1] = true;
    game.cells[1][2] = true;
    game.cells[2][0] = true;
    game.cells[2][1] = true;
    game.cells[2][2] = true;

    int generation = 0;
    bool running = true;
    bool paused = false;
    bool needs_render = true;

    terminal_init();

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
            terminal_clear();
            printf("Generation: %d  ", generation);

            printf("Interval: %llu ms",
                   (unsigned long long)generation_interval_ms);

            if (paused)
                printf(" [PAUSED]");

            putchar('\n');
            terminal_render(&game);

            needs_render = false;
        }

        Sleep(10);
    }

    return EXIT_SUCCESS;
}
