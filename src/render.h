#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>
#include "snake.h"

WINDOW *init_screen(void);
void draw_game(WINDOW *win, game *g);
void draw_test_snake(WINDOW *game_win);

#endif // RENDER_H
