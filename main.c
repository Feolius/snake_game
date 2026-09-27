#include <unistd.h>
#include <ncurses.h>

#include "snake.h"
#include "render.h"
#include "log.h"

int main(void) {
    reset_flog();

    WINDOW *game_win = init_screen();

    int max_y, max_x;
    getmaxyx(game_win, max_y, max_x);
    int size_x = ((max_x + 1) < MAX_WIDTH) ? (max_x + 1) : MAX_WIDTH;
    int size_y = ((max_y + 1) < MAX_HEIGHT) ? (max_y + 1) : MAX_HEIGHT;

    game *g = init_game(size_x, size_y);

    draw_snake(game_win, g->snake);
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
        draw_snake(game_win, g->snake);
        wrefresh(game_win);
        sleep(1);
    }

    curs_set(1);
    endwin();
    return 0;
}
