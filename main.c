#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "snake.h"
#include "render.h"
#include "log.h"

int main(void) {
    sleep(2);
    reset_flog();
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = TICK_TIME * 1000000;

    game_screen *screen = init_screen();

    int size_y, size_x;
    WINDOW *game_win = screen->game_window;
    WINDOW *score_win = screen->score_window;
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
        if (last == KEY_UP && dir != DOWN) {
            dir = UP;
        } else if (last == KEY_DOWN && dir != UP) {
            dir = DOWN;
        } else if (last == KEY_LEFT && dir != RIGHT) {
            dir = LEFT;
        } else if (last == KEY_RIGHT && dir != LEFT) {
            dir = RIGHT;
        }
        game_tick(g, dir);
        draw_game(game_win, g);
        draw_score(score_win, g);
        if (g->loose) {
            break;
        }
        nanosleep(&ts, NULL);
    }

    nodelay(stdscr, FALSE);
    while (getch() != 'q') {

    }

    curs_set(1);
    endwin();
    return 0;
}
