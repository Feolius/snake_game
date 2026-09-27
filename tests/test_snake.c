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

void test_

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_game_tick_moves_snake_right);
    return UNITY_END();
}
