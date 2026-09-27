#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define MAX_WIDTH 50
#define MAX_HEIGHT 50
#define INIT_LEN 4

typedef struct {
    int x;
    int y;
} point;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} direction;

struct segment {
    point* start;
    int length;
    direction dir;
    struct segment* next;
    struct segment* prev;
};

typedef struct segment segment;

typedef struct {
    segment* first_seg;
    segment* last_seg;
    int length;
} snake;

typedef struct {
    int size_x;
    int size_y;
    snake* snake;
    point* food;
} game;

// Game logic
game *init_game(int size_x, int size_y);
void game_tick(game *game, direction next_dir);
bool point_belongs_to_segment(point *pnt, segment *seg);
bool point_belongs_to_snake(point *pnt, snake *snk);

point* new_point(int x, int y);
segment* new_segment(point* start, int length, direction dir);

// Test helpers
snake *build_test_snake(void);

#endif // SNAKE_H
