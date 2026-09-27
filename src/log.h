#ifndef SNAKE_GAME_LOG_H
#define SNAKE_GAME_LOG_H

void reset_flog(void);
void flog(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif //SNAKE_GAME_LOG_H
