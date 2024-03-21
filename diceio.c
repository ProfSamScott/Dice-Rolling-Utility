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

#define BUFFER_SIZE 10000

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
            return 0;
        }
    }
    *pos = *pos + 1;
    while (**pos == ' ' || **pos == '\t')
        *pos = *pos + 1;
    return num;
}

int remove_whitespace(char *s) {
// TODO - 3d5 3d4
//    puts("remove_ws");
    int j = 0;
    char prev = 'x';
    for (int i=0; i<strlen(s); i++) {
//        printf("%d %d %c %c\n",i,j,s[i],s[j]);
        if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t') {
            s[j] = s[i];
            j++;
        } 
    }
    s[j] = '\0';
    return 0;
}

void dialog(flags f) {

    char raw[BUFFER_SIZE];
    char *input, *rewind;
    int total = 0;
    int state = ADD;
    bool error = false;

    if (f.verbose)
        puts("Enter some dice strings!");

    while (true) { 
        if (f.verbose)
            printf(">>> ");
        char *result = fgets(raw, BUFFER_SIZE, stdin);
        if (result == NULL || raw[0] == 'q' || raw[0] == 'Q')
            return;
        remove_whitespace(raw);
        int n = get_number(raw, &rewind);
        for (int i = 0; i < n; i++) {
            input = rewind;
            while (input != NULL && input[0] != '\0') {
                if (input[0] == 'c' || input[0] == 'C') {
                    total = 0;
                    state = CLR;
                    input++;
                } else if (input[0] == '+') {
                    if (f.verbose) 
                        printf("+ ");
                    state = ADD;
                    input++;
                } else if (input[0] == '-') {
                    if (f.verbose)
                        printf("- ");
                    state = SUB;
                    input++;
                } else if (input[0] == '*') {
                    if (f.verbose)
                        printf("* ");
                    state = MUL;
                    input++;
                } else if (input[0] == '/') {
                    if (f.verbose)
                        printf("/ ");
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
