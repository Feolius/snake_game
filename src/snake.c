#include "snake.h"

#include <stdlib.h>
#include <time.h>
#include "log.h"

bool point_belongs_to_segment(point *pnt, segment *seg) {
    point *start = seg->start;
    if (start->x != pnt->x && start->y != pnt->y) {
        return false;
    }
    if (start->x == pnt->x) {
        if (seg->dir == UP || seg->dir == DOWN) {
            return false;
        }
        if (seg->dir == LEFT) {
            if (pnt->x > start->x || pnt->x < (start->x - (seg->length - 1))) {
                return false;
            }
            return true;
        }
        if (pnt->x < start->x || pnt->x > (start->x + (seg->length - 1))) {
            return false;
        }
        return true;
    }
    if (start->y == pnt->y) {
        if (seg->dir == LEFT || seg->dir == RIGHT) {
            return false;
        }
        if (seg->dir == UP) {
            if (pnt->y > start->y || pnt->y < (start->y - (seg->length - 1))) {
                return false;
            }
            return true;
        }
        if (pnt->y < start->y || pnt->y > (start->y + (seg->length - 1))) {
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
        seg = seg->next;
    } while (seg != NULL);
    return false;
}

game *init_game(int size_x, int size_y) {
    flog("init_game");
    srand(time(NULL));

    int start_x = size_x / 2;
    int start_y = size_y / 2;

    point *start = malloc(sizeof(point));
    start->x = start_x;
    start->y = start_y;

    segment *seg = malloc(sizeof(segment));
    seg->start = start;
    seg->length = INIT_LEN;
    seg->dir = RIGHT;
    seg->next = NULL;
    seg->prev = NULL;

    snake *snk = malloc(sizeof(snake));
    snk->first_seg = seg;
    snk->last_seg = seg;
    snk->length = 1;

    point *food = malloc(sizeof(point));
    food->x = rand() % size_x;
    food->y = rand() % size_y;

    game *g = malloc(sizeof(game));
    g->size_x = size_x;
    g->size_y = size_y;
    g->snake = snk;
    g->food = food;

    return g;
}

void game_tick(game *game, direction next_dir) {
    snake *snake = game->snake;
    segment *first_seg = snake->first_seg;
    if (next_dir != first_seg->dir) {
        flog("dir %d", next_dir);
        segment *new_first_seg = malloc(sizeof(segment));
        new_first_seg->dir = next_dir;
        point *new_start = malloc(sizeof(point));
        new_start->x = first_seg->start->x;
        new_start->y = first_seg->start->y;
        new_first_seg->start = new_start;
        // We are increasing length below. it will be 1.
        new_first_seg->length = 0;
        new_first_seg->next = NULL;
        new_first_seg->prev = first_seg;
        first_seg->next = new_first_seg;
        first_seg = new_first_seg;
        snake->first_seg = new_first_seg;
        snake->length += 1;
    }
    if (first_seg->dir == UP) {
        first_seg->start->y -= 1;
    } else if (first_seg->dir == DOWN) {
        first_seg->start->y += 1;
    } else if (first_seg->dir == RIGHT) {
        first_seg->start->x += 1;
    } else {
        first_seg->start->x -= 1;
    }

    if (snake->length > 1) {
        first_seg->length += 1;
        segment *last_seg = snake->last_seg;
        last_seg->length -= 1;
        if (last_seg->length == 0) {
            snake->length -= 1;
            snake->last_seg = last_seg->next;
            last_seg->next->prev = NULL;
            free(last_seg->start);
            free(last_seg);
        }
    }
}

snake *build_test_snake(void) {
    point *start1 = malloc(sizeof(point));
    start1->x = 25;
    start1->y = 25;
    segment *seg1 = malloc(sizeof(segment));
    seg1->start = start1;
    seg1->length = 4;
    seg1->dir = RIGHT;
    seg1->next = NULL;

    point *start2 = malloc(sizeof(point));
    start2->x = 21;
    start2->y = 25;
    segment *seg2 = malloc(sizeof(segment));
    seg2->start = start2;
    seg2->length = 2;
    seg2->dir = UP;
    seg2->next = seg1;
    seg2->prev = NULL;

    seg1->prev = seg2;

    snake *sn = malloc(sizeof(snake));
    sn->first_seg = seg1;
    sn->last_seg = seg2;
    sn->length = 2;
    return sn;
}
