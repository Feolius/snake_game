#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "snake.h"
#include "render.h"
#include "log.h"

int main(void) {
    reset_flog();
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = TICK_TIME * 1000000;

    WINDOW *game_win = init_screen();

    int size_y, size_x;
    getmaxyx(game_win, size_y, size_x);

    game *g = init_game(size_x, size_y);

    draw_game(game_win, g);
    wrefresh(game_win);
    direction dir = RIGHT;

    while (true) {
        int ch, last = ERR;
        while ((ch = getch()) != ERR) {
            last = ch;
        }
        if (last == KEY_UP) {
            dir = UP;
        } else if (last == KEY_DOWN) {
            dir = DOWN;
        } else if (last == KEY_LEFT) {
            dir = LEFT;
        } else if (last == KEY_RIGHT) {
            dir = RIGHT;
        }
        game_tick(g, dir);
        werase(game_win);
        draw_game(game_win, g);
        wrefresh(game_win);
        nanosleep(&ts, NULL);
    }

    curs_set(1);
    endwin();
    return 0;
}
