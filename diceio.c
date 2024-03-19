/* TODO: c(lear), 3d6 without + or - performs a clear operation.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "parser.h"
#include "diceio.h"

int get_number(char* s, char **pos) {
    *pos = strchr(s, ':');
    if (*pos == NULL) {
        *pos = s;
        return 1;
    }
    int num = 0;
    for (; s < *pos; s++) {
        if (*s >= '0' && *s <= '9') {
            num = num * 10 + (*s - '0');
        } else {
            printf("ERROR near %s\n",s);
            return 0;
        }
    }
    *pos = *pos + 1;
    while (**pos == ' ' || **pos == '\t')
        *pos = *pos + 1;
    return num;
}

void dialog(flags f) {

    char raw[100000];
    char *input, *rewind;
    int total = 0;
    int state = ADD;
    bool error = false;

    if (f.verbose)
        puts("Enter some dice strings!");

    while (true) { 
        int result = scanf("%s",raw);
        int n = get_number(raw, &rewind);
        for (int i = 0; i < n; i++) {
            input = rewind;
            while (input != NULL && input[0] != '\0') {
                if (result == EOF || input[0] == 'q' || input[0] == 'Q')
                    return;
                if (input[0] == 'c' || input[0] == 'C') {
                    total = 0;
                    state = CLR;
                    input++;
                } else if (input[0] == '+') {
                    if (f.verbose) 
                        printf("+");
                    state = ADD;
                    input++;
                } else if (input[0] == '-') {
                    if (f.verbose)
                        printf("-");
                    state = SUB;
                    input++;
                } else if (input[0] == '*') {
                    if (f.verbose)
                        printf("*");
                    state = MUL;
                    input++;
                } else if (input[0] == '/') {
                    if (f.verbose)
                        printf("/");
                    state = DIV;
                    input++;
                } else if (input[0] == '=') {
                    if (f.verbose)
                        printf("==============\n");
                    printf("%d\n",total);
                    if (f.verbose)
                        printf("\n");
                    state = CLR;
                    input++;
                } else {
                    char *left;
                    diceset d = makeSet(input, &left);
                    input = left;
                    //printf("DEBUG: %s\n", left);
                    if (d.sides >= 0 && d.num > 0) {
                        error = false;
                        int result = rollset(d, f);
                        if (state == ADD) {
                            total += result;
                        } else if (state == SUB) {
                            total -= result;
                        } else if (state == MUL) {
                            total *= result;
                        } else if (state == DIV) {
                            total /= result;
                        } else if (state == CLR) {
                            total = result;
                        }
                        state = CLR;
                    } else {
                        if (!error)
                            printf("\n{ERROR near '%s'}\n",input);
                        input++;
                        error = true;
                    }
                } // else if chain
            } // while
        } // for
    } //while (true)
}
