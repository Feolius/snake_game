#include "snake.h"

#include <stdlib.h>
#include <time.h>
#include "log.h"

point* new_point(int x, int y) {
    point *pnt = malloc(sizeof(point));
    pnt->x = x;
    pnt->y = y;
    return pnt;
}

segment* new_segment(point *start, int length, direction dir) {
    segment *seg = malloc(sizeof(segment));
    seg->start = start;
    seg->length = length;
    seg->dir = dir;
    seg->next = NULL;
    seg->prev = NULL;
    return seg;
}

bool point_belongs_to_segment(point *pnt, segment *seg) {
    point *start = seg->start;
    if (start->x != pnt->x && start->y != pnt->y) {
        return false;
    }
    if (start->x == pnt->x && start->y == pnt->y) {
        return true;
    }
    if (start->x == pnt->x) {
        if (seg->dir == LEFT || seg->dir == RIGHT) {
            return false;
        }
        if (seg->dir == UP) {
            if (pnt->y < start->y || pnt->y > (start->y + (seg->length - 1))) {
                return false;
            }
            return true;
        }
        if (pnt->y < (start->y - (seg->length - 1)) || pnt->y > start->y) {
            return false;
        }
        return true;
    }
    if (start->y == pnt->y) {
        if (seg->dir == UP || seg->dir == DOWN) {
            return false;
        }
        if (seg->dir == LEFT) {
            if (pnt->x < start->x || pnt->x > (start->x + (seg->length - 1))) {
                return false;
            }
            return true;
        }
        if (pnt->x < (start->x - (seg->length - 1)) || pnt->x > start->x) {
            return false;
        }
        return true;
    }
    return false;
}

bool point_belongs_to_snake(point *pnt, snake *snk) {
    segment *seg = snk->first_seg;
    do {
        if (point_belongs_to_segment(pnt, seg)) {
            return true;
        }
        seg = seg->prev;
    } while (seg != NULL);
    return false;
}

void regenerate_food(game *g) {
    do {
        if (g->food != NULL) {
            free(g->food);
        }
        g->food = new_point(rand() % (g->size_x - 1), rand() % (g->size_y - 1));
    } while (point_belongs_to_snake(g->food, g->snake));
}


static bool point_is_tail(point *pnt, snake *snk) {
    segment *last = snk->last_seg;
    point tail;
    if (last->dir == UP) {
        tail.x = last->start->x;
        tail.y = last->start->y + (last->length - 1);
    } else if (last->dir == DOWN) {
        tail.x = last->start->x;
        tail.y = last->start->y - (last->length - 1);
    } else if (last->dir == RIGHT) {
        tail.x = last->start->x - (last->length - 1);
        tail.y = last->start->y;
    } else {
        tail.x = last->start->x + (last->length - 1);
        tail.y = last->start->y;
    }
    return pnt->x == tail.x && pnt->y == tail.y;

}

game *init_game(int size_x, int size_y) {
    flog("init_game");
    srand(time(NULL));

    int start_x = size_x / 2;
    int start_y = size_y / 2;

    segment *seg = new_segment(new_point(start_x, start_y), INIT_LEN, RIGHT);

    snake *snk = malloc(sizeof(snake));
    snk->first_seg = seg;
    snk->last_seg = seg;
    snk->length = 1;

    game *g = malloc(sizeof(game));
    g->size_x = size_x;
    g->size_y = size_y;
    g->score = 0;
    g->snake = snk;
    g->food = NULL;
    g->loose = false;
    regenerate_food(g);

    return g;
}

void game_tick(game *game, direction next_dir) {
    snake *snk = game->snake;
    segment *first_seg = snk->first_seg;
    if (next_dir != first_seg->dir) {
        flog("dir %d", next_dir);
        point *new_start = new_point(first_seg->start->x, first_seg->start->y);
        // We are increasing length below. it will be 1.
        segment *new_first_seg = new_segment(new_start, 0, next_dir);
        new_first_seg->prev = first_seg;
        first_seg->next = new_first_seg;
        first_seg = new_first_seg;
        snk->first_seg = new_first_seg;
        snk->length += 1;
    }

    point* next_start = new_point(first_seg->start->x, first_seg->start->y);
    if (first_seg->dir == UP) {
        next_start->y -= 1;
    } else if (first_seg->dir == DOWN) {
        next_start->y += 1;
    } else if (first_seg->dir == RIGHT) {
        next_start->x += 1;
    } else {
        next_start->x -= 1;
    }

    // Boundaries check
    if (next_start->x == -1 || next_start->x == game->size_x ||
        next_start->y == -1 || next_start->y == game->size_y) {
        game->loose = true;
        return;
    }

    // Self damage
    if (point_belongs_to_snake(next_start, game->snake) && !point_is_tail(next_start, game->snake)) {
        game->loose = true;
        return;
    }

    free(first_seg->start);
    first_seg->start = next_start;

    if (first_seg->start->x == game->food->x && first_seg->start->y == game->food->y) {
        first_seg->length += 1;
        game->score += 1;
        regenerate_food(game);
        return;
    }

    if (snk->length > 1) {
        first_seg->length += 1;
        segment *last_seg = snk->last_seg;
        last_seg->length -= 1;
        if (last_seg->length == 0) {
            snk->length -= 1;
            snk->last_seg = last_seg->next;
            last_seg->next->prev = NULL;
            free(last_seg->start);
            free(last_seg);
        }
    }
}

snake *build_test_snake(int size_x, int size_y) {
    int start_x = size_x / 2;
    int start_y = size_y / 2;

    segment *seg1 = new_segment(new_point(start_x, start_y), 1, RIGHT);

    segment *seg2 = new_segment(new_point(start_x - 1, start_y), 1, DOWN);
    seg2->next = seg1;
    seg1->prev = seg2;

    segment *seg3 = new_segment(new_point(start_x - 1, start_y - 1), 2, LEFT);
    seg3->next = seg2;
    seg2->prev = seg3;

    segment *seg4 = new_segment(new_point(start_x + 1, start_y - 1), 5, UP);
    seg4->next = seg3;
    seg3->prev = seg4;

    snake *sn = malloc(sizeof(snake));
    sn->first_seg = seg1;
    sn->last_seg = seg4;
    sn->length = 4;
    return sn;
}
