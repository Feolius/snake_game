#include <stdlib.h>

#include "unity.h"
#include "../src/snake.h"

void setUp(void) {}
void tearDown(void) {}

void test_game_tick_moves_snake_right(void) {
    game *g = init_game(50, 50);
    int old_x = g->snake->first_seg->start->x;

    game_tick(g, RIGHT);

    TEST_ASSERT_EQUAL_INT(old_x + 1, g->snake->first_seg->start->x);
}

void test_point_belongs_to_segment(void) {
    // --- UP: start (25,25), length 5 → body y: 25..21 ---
    segment *seg = new_segment(
        new_point(25, 25),
        5,
        UP
        );
    bool res = point_belongs_to_segment(new_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start");
    res = point_belongs_to_segment(new_point(25, 24), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point higher than start and direction UP");
    res = point_belongs_to_segment(new_point(25, 26), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point lower than start and direction UP");
    res = point_belongs_to_segment(new_point(26, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (26, 25) segment (25, 25, UP)");
    res = point_belongs_to_segment(new_point(24, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (24, 25) segment (25, 25, UP)");
    res = point_belongs_to_segment(new_point(25, 21), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "false: point (24, 21) segment (25, 25, UP)");
    res = point_belongs_to_segment(new_point(25, 20), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (24, 20) segment (25, 25, UP)");

    // --- DOWN: start (25,25), length 5 → body y: 25..29 ---
    seg = new_segment(
        new_point(25, 25),
        5,
        DOWN
        );
    res = point_belongs_to_segment(new_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start (DOWN)");
    res = point_belongs_to_segment(new_point(25, 26), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point one step in DOWN direction");
    res = point_belongs_to_segment(new_point(25, 24), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point one step opposite to DOWN direction");
    res = point_belongs_to_segment(new_point(26, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (26, 25) segment (25, 25, DOWN)");
    res = point_belongs_to_segment(new_point(24, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (24, 25) segment (25, 25, DOWN)");
    res = point_belongs_to_segment(new_point(25, 29), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point at last cell (25, 29) segment (25, 25, DOWN)");
    res = point_belongs_to_segment(new_point(25, 30), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point beyond end (25, 30) segment (25, 25, DOWN)");

    // --- LEFT: start (25,25), length 5 → body x: 25..21 ---
    seg = new_segment(
        new_point(25, 25),
        5,
        LEFT
        );
    res = point_belongs_to_segment(new_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start (LEFT)");
    res = point_belongs_to_segment(new_point(24, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point one step in LEFT direction");
    res = point_belongs_to_segment(new_point(26, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point one step opposite to LEFT direction");
    res = point_belongs_to_segment(new_point(25, 26), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 26) segment (25, 25, LEFT)");
    res = point_belongs_to_segment(new_point(25, 24), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 24) segment (25, 25, LEFT)");
    res = point_belongs_to_segment(new_point(21, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point at last cell (21, 25) segment (25, 25, LEFT)");
    res = point_belongs_to_segment(new_point(20, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point beyond end (20, 25) segment (25, 25, LEFT)");

    // --- RIGHT: start (25,25), length 5 → body x: 25..29 ---
    seg = new_segment(
        new_point(25, 25),
        5,
        RIGHT
        );
    res = point_belongs_to_segment(new_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start (RIGHT)");
    res = point_belongs_to_segment(new_point(26, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point one step in RIGHT direction");
    res = point_belongs_to_segment(new_point(24, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point one step opposite to RIGHT direction");
    res = point_belongs_to_segment(new_point(25, 26), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 26) segment (25, 25, RIGHT)");
    res = point_belongs_to_segment(new_point(25, 24), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 24) segment (25, 25, RIGHT)");
    res = point_belongs_to_segment(new_point(29, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point at last cell (29, 25) segment (25, 25, RIGHT)");
    res = point_belongs_to_segment(new_point(30, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point beyond end (30, 25) segment (25, 25, RIGHT)");
}

void test_generate_food(void) {
    game *game = init_game(8, 8);
    for (int i = 0; i < 20; i++) {
        point food = *(game->food);
        char msg[128];
        snprintf(msg, sizeof(msg), "point (%d, %d)", food.x, food.y);
        TEST_ASSERT_FALSE_MESSAGE(point_belongs_to_snake(&food, game->snake), msg);
        regenerate_food(game);
    }
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_game_tick_moves_snake_right);
    RUN_TEST(test_point_belongs_to_segment);
    RUN_TEST(test_generate_food);
    return UNITY_END();
}
