#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "parser.h"

// s is a string with no leading/traling whitespace
diceset makeSet(char *s) {
    diceset result;
    result.sides = -1;
    int buffer = 0;

    int state = STATE_NUM;
    for(int i=0; i<strlen(s); i++) {
        if (state == STATE_NUM) {
            if (s[i] >= '0' && s[i] <= '9') {
                buffer = buffer * 10 + s[i]-'0';
            } else if (s[i] == 'd' || s[i] == 'D') {
                if (buffer <= 0) {
                    return result;
                }
                state = STATE_D;
                result.num = buffer;
                buffer = 0;
            } else {
                return result;
            }
        } else if (state == STATE_D) {
            if (s[i] >= '0' && s[i] <= '9') {
                buffer = buffer * 10 + s[i] - '0';
                state = STATE_SIDES;
            } else {
                return result;
            }
        } else if (state == STATE_SIDES) {
            if (s[i] >= '0' && s[i] <= '9') {
                buffer = buffer * 10 + s[i] - '0';
            } else {
                return result;
            }
        }
    }
    if (state == STATE_SIDES && buffer > 0) {
        result.sides = buffer;
    } else if (state == STATE_NUM && buffer > 0) {
        result.num = buffer;
        result.sides = 0; // constant
    }
    return result;
}

int rollset(diceset d, flags f) {
    if (d.sides == 0) {
        return d.num;
    }
    int sum = 0;
    for (int i=0; i<d.num; i++) {
        int roll = (int)((double)rand()/RAND_MAX*d.sides)+1; 
        sum += roll;
        if (f.verbose) {
            if (i > 0) 
                printf("+ ");
            printf("%d ", roll);
        }
    }
    if (f.verbose)
        printf("= ");
    return sum;
}
