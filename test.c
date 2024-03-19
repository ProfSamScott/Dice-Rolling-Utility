#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char response[10];
    int len = sizeof(response);

    int i = 0;
    do {
        response[i++] = getchar();
    } while (i<10 && response[i-1] != '\n');
    response[i-1] = '\0';

    puts(response);

    char buffer[40];
    fgets(buffer, 40, stdin);
    puts(buffer);
    fgets(buffer, 40, stdin);
    puts(buffer);
    char *next;
    long l = strtol(buffer, &next, 10);
    printf("%ld -- %s\n",l, next);
}
