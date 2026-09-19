cmake_minimum_required(VERSION 4.3)
project(snake_game C)

set(CMAKE_C_STANDARD 17)

set(NCURSES_INCLUDE_DIR /opt/homebrew/opt/ncurses/include)
set(NCURSES_LIB_DIR     /opt/homebrew/opt/ncurses/lib)

add_executable(snake_game
        main.c)

target_include_directories(snake_game PRIVATE ${NCURSES_INCLUDE_DIR})
target_link_directories(snake_game PRIVATE ${NCURSES_LIB_DIR})
target_link_libraries(snake_game PRIVATE ncurses)