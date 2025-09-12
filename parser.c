#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include "parser.h"

// state variables for makeSet
// here's a change
#define STATE_NUM 0 
#define STATE_D 1
#define STATE_SIDES 2

/* makeSet()
 * s: a string with no leading or trailing whitespace
 * *remaining: a pointer to what remains after the first diceset
 * is processed
 * 
 * return: a diceset structure representing the dice set found
 * 
 * A diceset is in the format "3d6" or "d20" or "12". This function 
 * assumes  * that s starts with a valid diceset and parses it. If 
 * the set is not valid, errors are indicated with -1 values in the 
 * diceset returned.
 */
diceset makeSet(char *s, char **remaining)
{
    diceset result;
    result.num = -1;
    result.sides = -1;
    int buffer = 0;

    int state = STATE_NUM;
    int i;
    for (i = 0; i < strlen(s); i++)
    {
        if (state == STATE_NUM)
        { // reading the number of dice in the set
            if (s[i] >= '0' && s[i] <= '9')
            {
                buffer = buffer * 10 + s[i] - '0';
            }
            else if (s[i] == 'd' || s[i] == 'D')
            {
                state = STATE_D;
                if (buffer <= 0)
                    result.num = 1;
                else
                    result.num = buffer;
                buffer = 0;
            }
            else
            {
                break;
            }
        }
        else if (state == STATE_D)
        { // reading the "d" or "D" separator
            if (s[i] >= '0' && s[i] <= '9')
            {
                buffer = buffer * 10 + s[i] - '0';
                state = STATE_SIDES;
            }
            else
            {
                break;
            }
        }
        else if (state == STATE_SIDES)
        { // reading the number of sides in the set
            if (s[i] >= '0' && s[i] <= '9')
            {
                buffer = buffer * 10 + s[i] - '0';
            }
            else
            {
                break;
            }
        }
    }
    if (state == STATE_SIDES && buffer > 0)
    { // assign the sides
        result.sides = buffer;
    }
    else if (state == STATE_NUM && buffer > 0)
    { // we never saw the "d" separator, so this is a constant (e.g., "23")
        result.num = buffer;
        result.sides = 0; // constant
    }
    *remaining = s + i;
    //    printf("LEAVING PARSER: %s\n",*remaining);
    return result;
}

/* rollset()
 * 
 * d: a diceset to roll
 * f: command line flags
 * 
 * return: the amount rolled
 * 
 * This function simulates the rolling of a dice set
 * and returns the result.
 */
int rollset(diceset d, flags f)
{
    if (f.verbose)
    {
        if (d.sides > 0)
            printf("%dd%d [", d.num, d.sides);
    }
    if (d.sides == 0)
    { // this is a constant (e.g., "23")
        if (f.verbose)
            printf("%d\n", d.num);
        return d.num;
    }
    int sum = 0;
    for (int i = 0; i < d.num; i++)
    {
        int roll = (int)((double)rand() / RAND_MAX * d.sides) + 1;
        sum += roll;
        if (f.verbose)
        {
            if (i > 0)
                printf(" ");
            printf("%d", roll);
        }
    }
    if (f.verbose)
        printf("] %d\n", sum);
    return sum;
}
