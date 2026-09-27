#include "render.h"
#include "snake.h"

#include <unistd.h>
#include <log.h>

WINDOW *init_screen(void) {
    flog("init_screen");
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int size_x = (max_x < MAX_WIDTH) ? max_x : MAX_WIDTH;
    int size_y = (max_y < MAX_HEIGHT) ? max_y : MAX_HEIGHT;

    WINDOW *borders_win = newwin(size_y, size_x, 0, 0);
    WINDOW *game_win = newwin(size_y - 2, size_x - 2, 1, 1);
    refresh();
    box(borders_win, 0, 0);
    wrefresh(borders_win);
    return game_win;
}

static void draw_segment(WINDOW *win, segment *seg) {
    if (seg->dir == UP) {
        for (int dy = 0; dy < seg->length; dy++) {
            mvwaddch(win, seg->start->y + dy, seg->start->x, '0');
        }
    } else if (seg->dir == DOWN) {
        for (int dy = 0; dy < seg->length; dy++) {
            mvwaddch(win, seg->start->y - dy, seg->start->x, '0');
        }
    } else if (seg->dir == RIGHT) {
        for (int dx = 0; dx < seg->length; dx++) {
            mvwaddch(win, seg->start->y, seg->start->x - dx, '0');
        }
    } else if (seg->dir == LEFT) {
        for (int dx = 0; dx < seg->length; dx++) {
            mvwaddch(win, seg->start->y, seg->start->x + dx, '0');
        }
    }
}

static void draw_snake(WINDOW *win, snake *snk) {
    segment *seg = snk->first_seg;
    while (seg != NULL) {
        draw_segment(win, seg);
        seg = seg->prev;
    }
}

void draw_game(WINDOW *win, game *g) {
    draw_snake(win, g->snake);
    mvwaddch(win, g->food->y, g->food->x, '*');
}

void draw_test_snake(WINDOW *game_win) {
    int max_y, max_x;
    getmaxyx(game_win, max_y, max_x);
    int size_x = ((max_x + 1) < MAX_WIDTH) ? (max_x + 1) : MAX_WIDTH;
    int size_y = ((max_y + 1) < MAX_HEIGHT) ? (max_y + 1) : MAX_HEIGHT;

    game *g = init_game(size_x, size_y);
    snake *sn = build_test_snake();
    g->snake = sn;
    draw_snake(game_win, sn);
    wrefresh(game_win);
    refresh();
    for (int i = 0; i < 6; i++) {
        sleep(2);
        game_tick(g, RIGHT);
        werase(game_win);
        draw_snake(game_win, sn);
        wrefresh(game_win);
    }
}
