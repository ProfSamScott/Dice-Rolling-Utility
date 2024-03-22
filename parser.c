#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include "parser.h"

#define STATE_NUM 0
#define STATE_D 1
#define STATE_SIDES 2

// s is a string with no leading/traling whitespace
diceset makeSet(char *s, char **remaining) {
//    printf("ENTERING PARSER: %s\n",s);
    diceset result;
    result.num = -1;
    result.sides = -1;
    int buffer = 0;

    int state = STATE_NUM;
    int i;
    for(i=0; i<strlen(s); i++) {
        if (state == STATE_NUM) {
            if (s[i] >= '0' && s[i] <= '9') {
                buffer = buffer * 10 + s[i]-'0';
            } else if (s[i] == 'd' || s[i] == 'D') {
                state = STATE_D;
                if (buffer <= 0)
                    result.num = 1;
                else 
                    result.num = buffer;
                buffer = 0;
            } else {
                break;
            }
        } else if (state == STATE_D) {
            if (s[i] >= '0' && s[i] <= '9') {
                buffer = buffer * 10 + s[i] - '0';
                state = STATE_SIDES;
            } else {
                break;
            }
        } else if (state == STATE_SIDES) {
            if (s[i] >= '0' && s[i] <= '9') {
                buffer = buffer * 10 + s[i] - '0';
            } else {
                break;
            }
        }
    }
    if (state == STATE_SIDES && buffer > 0) {
        result.sides = buffer;
    } else if (state == STATE_NUM && buffer > 0) {
        result.num = buffer;
        result.sides = 0; // constant
    }
    *remaining=s+i;
//    printf("LEAVING PARSER: %s\n",*remaining);
    return result;
}

int rollset(diceset d, flags f) {
    if (f.verbose) {
        if (d.sides > 0)
            printf("%dd%d [",d.num, d.sides);
    }
    if (d.sides == 0) {
        if (f.verbose)
            printf("%d\n",d.num);
        return d.num;
    }
    int sum = 0;
    for (int i=0; i<d.num; i++) {
        int roll = (int)((double)rand()/RAND_MAX*d.sides)+1; 
        sum += roll;
        if (f.verbose) {
            if (i > 0) 
                printf(" ");
            printf("%d", roll);
        }
    }
    if (f.verbose)
        printf("] %d\n", sum);
    return sum;
}
