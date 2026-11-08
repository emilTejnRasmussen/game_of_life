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



    for (int gen = 0; gen < 10; gen++) {
        terminal_clear();

        printf("Generation %d.\n", gen);
        terminal_render(&game);
        
        Sleep(500);

        next_generation(&game);
    }

    return EXIT_SUCCESS;
}
