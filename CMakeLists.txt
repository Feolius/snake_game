cmake_minimum_required(VERSION 4.3)
project(snake_game C)

set(CMAKE_C_STANDARD 17)

set(NCURSES_INCLUDE_DIR /opt/homebrew/opt/ncurses/include)
set(NCURSES_LIB_DIR     /opt/homebrew/opt/ncurses/lib)

# --- Unity ---
add_library(unity STATIC vendor/unity/unity.c)
target_include_directories(unity PUBLIC vendor/unity)

# --- Чистая логика игры (без ncurses) ---
add_library(snake_logic STATIC src/snake.c
        src/log.c)
target_include_directories(snake_logic PUBLIC src)

# --- Рендер (с ncurses) ---
add_library(snake_render STATIC src/render.c)
target_include_directories(snake_render PUBLIC src ${NCURSES_INCLUDE_DIR})
target_link_directories(snake_render PUBLIC ${NCURSES_LIB_DIR})
target_link_libraries(snake_render PUBLIC ncurses snake_logic)

# --- Основное приложение ---
add_executable(snake_game main.c)
target_include_directories(snake_game PRIVATE src ${NCURSES_INCLUDE_DIR})
target_link_libraries(snake_game PRIVATE snake_render snake_logic)

# --- Тесты ---
enable_testing()

add_executable(test_snake tests/test_snake.c)
target_link_libraries(test_snake PRIVATE snake_logic unity)

add_test(NAME SnakeTests COMMAND test_snake)
