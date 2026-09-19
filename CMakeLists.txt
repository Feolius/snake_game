cmake_minimum_required(VERSION 4.3)
project(c_lang C)

set(CMAKE_C_STANDARD 17)

set(NCURSES_INCLUDE_DIR /opt/homebrew/opt/ncurses/include)
set(NCURSES_LIB_DIR     /opt/homebrew/opt/ncurses/lib)

add_executable(c_lang
        main.c)

target_include_directories(c_lang PRIVATE ${NCURSES_INCLUDE_DIR})
target_link_directories(c_lang PRIVATE ${NCURSES_LIB_DIR})
target_link_libraries(c_lang PRIVATE ncurses)