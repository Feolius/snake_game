#include <ncurses.h>
#include <stdlib.h>
#include <stdarg.h>


#define MAX_WIDTH 11
#define MAX_HEIGHT 11
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
    point* head;
    int length;
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

void draw_horizontal_line(int y, int len, char c) {
    for (int x = 0; x < len; x++) {
        mvaddch(y, x, c);
    }
}

void draw_vertical_line(int x, int len, char c) {
    for (int y = 0; y < len; y++) {
        mvaddch(y, x, c);
    }
}

void draw_field(int size_x, int size_y) {
    clear();
    draw_horizontal_line(0,  size_x, '$');
    draw_horizontal_line(size_y - 1, size_x, '$');
    draw_vertical_line(0, size_y, '$');
    draw_vertical_line(size_x - 1, size_y, '$');
}

void draw_segment(segment* seg) {
    if (seg->dir == UP) {
        for (int dy = 0; dy < seg->length; dy++) {
            mvaddch(seg->head->y + dy, seg->head->x, '0');
        }
    } else if (seg->dir == DOWN) {
        for (int dy = 0; dy < seg->length; dy++) {
            mvaddch(seg->head->y - dy, seg->head->x, '0');
        }
    } else if (seg->dir == RIGHT) {
        for (int dx = 0; dx < seg->length; dx++) {
            mvaddch(seg->head->y, seg->head->x - dx, '0');
        }
    } else if (seg->dir == LEFT) {
        for (int dx = 0; dx < seg->length; dx++) {
            mvaddch(seg->head->y, seg->head->x + dx, '0');
        }
    }
}

void init_game() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    flog("max y %d", max_x);

    int size_x = (max_x < MAX_WIDTH) ? max_x : MAX_WIDTH;
    int size_y = (max_y < MAX_HEIGHT) ? max_y : MAX_HEIGHT;
    draw_field(size_x, size_y);

    int start_x = size_x / 2;
    int start_y = size_y / 2;

    point head = {start_x, start_y};
    segment seg = {.head = &head, .length = INIT_LEN, .dir = DOWN};
    draw_segment(&seg);
}




int main(void)
{
    reset_flog();
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_game();
    refresh();

    int ch;
    while((ch = getch()) != 'q') {
    }

    curs_set(1);
    endwin();
    return 0;
}