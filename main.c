#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdarg.h>


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

typedef struct {
    point* start;
    point* end;
    direction dir;
} segment;


void reset_flog() {
    FILE *fp;

    fp = fopen("log.txt", "w");
    fclose(fp);
}

void flog(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

void flog(const char *fmt, ...) {
    FILE *fp = fopen("log.txt", "a");
    if (!fp) return;

    va_list args;
    va_start(args, fmt);
    vfprintf(fp, fmt, args);
    va_end(args);

    fputc('\n', fp);
    fclose(fp);
}

void put_char_at(int x, int y, char c) {
    // move(y, x);
    // addch(c);
    mvaddch(y, x, c);

    // refresh();
}


void draw_horizontal_line(int y, int len, char c) {
    for (int x = 0; x < len; x++) {
        put_char_at(x, y, c);
    }
}

void draw_vertical_line(int x, int len, char c) {
    for (int y = 0; y < len; y++) {
        put_char_at(x, y, c);
    }
}

void draw_field(int size_x, int size_y) {
    clear();
    draw_horizontal_line(0,  size_x, '$');
    draw_horizontal_line(size_y - 1, size_x, '$');
    draw_vertical_line(0, size_y, '$');
    draw_vertical_line(size_x - 1, size_y, '$');
    refresh();
}

segment* init_game() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    flog("max y %d", max_x);

    int size_x = (max_x < MAX_WIDTH) ? max_x : MAX_WIDTH;
    int size_y = (max_y < MAX_HEIGHT) ? max_y : MAX_HEIGHT;
    draw_field(size_x, size_y);

    int start_x = size_x / 2;
    int start_y = size_y / 2;

    segment* seg = malloc(sizeof(segment) * INIT_LEN);
}




int main(void)
{
    reset_flog();
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_game();

    int ch;
    while((ch = getch()) != 'q') {
    }

    endwin();
    return 0;
}