#include <stdlib.h>

#include "unity.h"
#include "../src/snake.h"

void test_point_belongs_to_segment(void) {
    // --- UP: start (25,25), length 5 → body y: 25..21 ---
    segment *seg = create_segment(
        create_point(25, 25),
        5,
        UP
        );
    bool res = point_belongs_to_segment(create_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start");
    res = point_belongs_to_segment(create_point(25, 24), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point higher than start and direction UP");
    res = point_belongs_to_segment(create_point(25, 26), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point lower than start and direction UP");
    res = point_belongs_to_segment(create_point(26, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (26, 25) segment (25, 25, UP)");
    res = point_belongs_to_segment(create_point(24, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (24, 25) segment (25, 25, UP)");
    res = point_belongs_to_segment(create_point(25, 21), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "false: point (24, 21) segment (25, 25, UP)");
    res = point_belongs_to_segment(create_point(25, 20), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (24, 20) segment (25, 25, UP)");

    // --- DOWN: start (25,25), length 5 → body y: 25..29 ---
    seg = create_segment(
        create_point(25, 25),
        5,
        DOWN
        );
    res = point_belongs_to_segment(create_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start (DOWN)");
    res = point_belongs_to_segment(create_point(25, 26), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point one step in DOWN direction");
    res = point_belongs_to_segment(create_point(25, 24), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point one step opposite to DOWN direction");
    res = point_belongs_to_segment(create_point(26, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (26, 25) segment (25, 25, DOWN)");
    res = point_belongs_to_segment(create_point(24, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (24, 25) segment (25, 25, DOWN)");
    res = point_belongs_to_segment(create_point(25, 29), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point at last cell (25, 29) segment (25, 25, DOWN)");
    res = point_belongs_to_segment(create_point(25, 30), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point beyond end (25, 30) segment (25, 25, DOWN)");

    // --- LEFT: start (25,25), length 5 → body x: 25..21 ---
    seg = create_segment(
        create_point(25, 25),
        5,
        LEFT
        );
    res = point_belongs_to_segment(create_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start (LEFT)");
    res = point_belongs_to_segment(create_point(24, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point one step in LEFT direction");
    res = point_belongs_to_segment(create_point(26, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point one step opposite to LEFT direction");
    res = point_belongs_to_segment(create_point(25, 26), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 26) segment (25, 25, LEFT)");
    res = point_belongs_to_segment(create_point(25, 24), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 24) segment (25, 25, LEFT)");
    res = point_belongs_to_segment(create_point(21, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point at last cell (21, 25) segment (25, 25, LEFT)");
    res = point_belongs_to_segment(create_point(20, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point beyond end (20, 25) segment (25, 25, LEFT)");

    // --- RIGHT: start (25,25), length 5 → body x: 25..29 ---
    seg = create_segment(
        create_point(25, 25),
        5,
        RIGHT
        );
    res = point_belongs_to_segment(create_point(25, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point same as start (RIGHT)");
    res = point_belongs_to_segment(create_point(26, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point one step in RIGHT direction");
    res = point_belongs_to_segment(create_point(24, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point one step opposite to RIGHT direction");
    res = point_belongs_to_segment(create_point(25, 26), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 26) segment (25, 25, RIGHT)");
    res = point_belongs_to_segment(create_point(25, 24), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point (25, 24) segment (25, 25, RIGHT)");
    res = point_belongs_to_segment(create_point(29, 25), seg);
    TEST_ASSERT_TRUE_MESSAGE(res, "true: point at last cell (29, 25) segment (25, 25, RIGHT)");
    res = point_belongs_to_segment(create_point(30, 25), seg);
    TEST_ASSERT_FALSE_MESSAGE(res, "false: point beyond end (30, 25) segment (25, 25, RIGHT)");
}
