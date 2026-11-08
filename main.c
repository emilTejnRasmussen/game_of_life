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

    terminal_init();

    while (running) {
        terminal_clear();

        printf("Generation: %d", generation);

        if (paused)
            printf(" [PAUSED]");

        putchar('\n');

        terminal_render(&game);
        int key = terminal_read_key();

        switch (key) {
        case 'Q':
        case 'q':
            running = false;
            break;

        case ' ':
            paused = !paused;
            break;
        }

        if (!running)
            break;

        Sleep(500);

        if (paused)
            continue;

        next_generation(&game);
        generation++;
    }

    return EXIT_SUCCESS;
}
