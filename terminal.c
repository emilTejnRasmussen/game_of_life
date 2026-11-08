#include "terminal.h"
#include "life.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define ALIVE "🟩"
#define DEAD "⬛"

#define COLOR_GREEN "\033[92m"
#define COLOR_YELLOW "\033[93m"
#define COLOR_GRAY "\033[90m"
#define COLOR_RESET "\033[0m"

static void render_header(const GameOfLife *game, int generation,
                          DWORD64 interval_ms, bool paused);

static void render_grid(const GameOfLife *game);

static void render_footer(void);

void terminal_init() {
    SetConsoleOutputCP(CP_UTF8);
    printf("\033[?1049h"); // Enter alternate screen
    printf("\033[?25l");   // Hide cursor

    fflush(stdout);
}

void terminal_clear(void) { printf("\033[2J\033[H"); }

void terminal_home(void) { printf("\033[H"); }

void terminal_render_frame(const GameOfLife *game, int generation,
                           DWORD64 interval_ms, bool paused) {
    terminal_home();

    render_header(game, generation, interval_ms, paused);
    render_grid(game);
    render_footer();

    fflush(stdout);
}

int terminal_read_key() {
    if (_kbhit()) {
        int key = _getch();
        return key;
    }

    return -1;
}

void terminal_cleanup(void) {
    printf("\033[?25h");   // Show cursor
    printf("\033[?1049l"); // Restore original screen
    fflush(stdout);
}

static void render_header(const GameOfLife *game, int generation,
                          DWORD64 interval_ms, bool paused) {
    int alive = life_count_alive(game);
    int total = ROWS * COLS;
    double density = (double)alive / total * 100.0;

    printf(COLOR_GREEN "\033[2k CONWAY'S GAME OF LIFE" COLOR_RESET);

    printf("                      ");
    printf(paused ? COLOR_YELLOW "\033[2k PAUSED" COLOR_RESET
                  : COLOR_GREEN "RUNNING" COLOR_RESET);
    printf("\n");

    printf(COLOR_GRAY
           "--------------------------------------------------" COLOR_RESET
           "\n\n");

    printf("\033[2K  %-12s %6d    %-12s %3d / %-3d\n", "Generation:", generation,
           "Population:", alive, total);

    printf("\033[2K  %-12s %5.1f%%    %-12s %4llu ms\n", "Density:", density,
           "Interval:", (unsigned long long)interval_ms);

    printf("\n");
}

static void render_grid(const GameOfLife *game) {
    for (int i = 0; i < ROWS; i++) {
        printf("  ");
        for (int j = 0; j < COLS; j++) {
            fputs(game->cells[i][j] ? ALIVE : DEAD, stdout);
        }
        putchar('\n');
    }

    fflush(stdout);
}

static void render_footer(void) {
    putchar('\n');

    printf("  CONTROLS\n");
    printf("  ----------------------------------------\n");
    printf("  [SPACE] Pause / Resume    [N] Next step\n");
    printf("  [R]     Randomize         [+] Faster\n");
    printf("  [Q]     Quit              [-] Slower\n");
}
