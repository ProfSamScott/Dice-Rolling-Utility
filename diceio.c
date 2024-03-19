/* TODO: +, -, *, / (round down), =, c(lear), 3d6 without + or - performs a clear operation.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "parser.h"
#include "diceio.h"

void dialog(flags f) {

    char raw[100000];
    char *input;
    int total = 0;
    int state = ADD;

    if (f.verbose)
        puts("Enter some dice strings!");

    do { 
        int result = scanf("%s",raw);
        input = raw;
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
                    printf("==> ");
                printf("%d\n",total);
                state = CLR;
                input++;
            } else {
                char *left;
                diceset d = makeSet(input, &left);
                input = left;
                //printf("DEBUG: %s\n", left);
                if (d.sides >= 0 && d.num > 0) {
                    int result = rollset(d, f);
                    if (f.verbose)
                        printf("%d\n", result);
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
                    printf("ERROR! %dd%d\n",d.num,d.sides);
                }
            }
        }
    } while (true);

}
