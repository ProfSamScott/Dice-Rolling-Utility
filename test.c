#include <stdio.h>
#include <string.h>

int main(void) {
    puts("Hi! Testing");
    char *s = "Hi there this is a test!";
    printf("%s\n",strchr(s, '!'));
    printf("%s\n",strchr(s, 'z'));
}
