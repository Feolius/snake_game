#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
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
    snake* snake;
} game;

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

WINDOW* init_screen() {
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int size_x = (max_x < MAX_WIDTH) ? max_x : MAX_WIDTH;
    int size_y = (max_y < MAX_HEIGHT) ? max_y : MAX_HEIGHT;

    WINDOW *borders_win = newwin(size_y, size_x, 0, 0);
    WINDOW *game_win = newwin(size_y - 2, size_x - 2, 1, 1);
    refresh();
    box(borders_win, 0, 0);
    wrefresh(borders_win);
    return game_win;
}

game *init_game(WINDOW* win) {
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    int size_x = (max_x < MAX_WIDTH) ? max_x : MAX_WIDTH;
    int size_y = (max_y < MAX_HEIGHT) ? max_y : MAX_HEIGHT;

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

    snake *snake = malloc(sizeof(snake));
    snake->first_seg = seg;
    snake->last_seg = seg;
    snake->length = 1;

    game *new_game = malloc(sizeof(game));
    new_game->snake = snake;

    return new_game;
}

void draw_segment(WINDOW* win, segment* seg) {
    if (seg->dir == UP) {
        for (int dy = 0; dy < seg->length; dy++) {
            mvwaddch(win, seg->start->y + dy, seg->start->x, '0');
        }
    } else if (seg->dir == DOWN) {
        for (int dy = 0; dy < seg->length; dy++) {
            mvwaddch(win, seg->start->y - dy, seg->start->x, '0');
        }
    } else if (seg->dir == RIGHT) {
        for (int dx = 0; dx < seg->length; dx++) {
            mvwaddch(win, seg->start->y, seg->start->x - dx, '0');
        }
    } else if (seg->dir == LEFT) {
        for (int dx = 0; dx < seg->length; dx++) {
            mvwaddch(win, seg->start->y, seg->start->x + dx, '0');
        }
    }
}

void draw_snake(snake* snake) {}

void game_tick(snake *snake, direction next_dir) {
    segment* first_seg = snake->first_seg;
    if (next_dir != first_seg->dir) {
        segment* new_first_seg = malloc(sizeof(segment));
        new_first_seg->dir = next_dir;
        new_first_seg->start = first_seg->start;
        // We are increasing length below. it will be 1.
        new_first_seg->length = 0;
        new_first_seg->next = first_seg;
        new_first_seg->prev = NULL;
        first_seg->prev = new_first_seg;
        if (snake->last_seg == NULL) {
            snake->last_seg = first_seg;
        }
        first_seg = new_first_seg;
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
        snake->last_seg->length -= 1;
        if (last_seg->length == 0) {
            snake->length -= 1;
            free(last_seg->start);
            free(last_seg);
        }
    }
}

int main(void)
{
    reset_flog();

    WINDOW* game_win = init_screen();

    game* game = init_game(game_win);
    draw_segment(game_win, game->snake->first_seg);
    wrefresh(game_win);
    // refresh();

    while (true) {
        int ch = getch();
        // flog("ch: %d", ch);
        if (ch == 'q') {
            break;
        }
        sleep(2);
    }

    curs_set(1);
    endwin();
    return 0;
}