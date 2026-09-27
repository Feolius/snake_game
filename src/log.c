#include <stdarg.h>
#include <stdio.h>

void reset_flog(void) {
    FILE *fp = fopen("log.txt", "w");
    fclose(fp);
}

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