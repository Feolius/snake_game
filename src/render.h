#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>
#include "snake.h"

typedef struct {
    WINDOW* game_window;
    WINDOW* score_window;
} game_screen;

game_screen *init_screen(void);
void draw_game(WINDOW *win, game *g);
void draw_score(WINDOW *win, game *g);
void draw_test_snake(WINDOW *game_win);

#endif // RENDER_H
