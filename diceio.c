/* Contains the basic I/O functions for the dice parser
 * The dialog function kicks things off.
 *
 * Sam Scott, McMaster University, 2024
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utilities.h"
#include "parser.h"
#include "diceio.h"

int get_number(char *s, char **pos);
int process_command_line(char *raw, flags f, int total, int *state);

// maximum input string length
#define BUFFER_SIZE 10000 

// State constants for process_command_line()
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define CLR 4

/* dialog() 
 *
 * f: contains important flags related to command line options
 *
 * Reads from stdin one line at a time and calls
 * process_command_line
 *
 * The "state" variable tracks the state of processing between
 * lines of input
 *
 * The "total" variable tracks the running total of dice commands
 * between lines of input
 */
void dialog(flags f)
{

    char raw[BUFFER_SIZE];
    int total = 0;
    int state = ADD;

    if (f.verbose)
        puts("Enter some dice strings!");

    while (true)
    {
        if (f.verbose)
            printf(">>> ");
        char *result = fgets(raw, BUFFER_SIZE, stdin);
        // check for end of input
        if (result == NULL || raw[0] == 'q' || raw[0] == 'Q')
            return;
        total = process_command_line(raw, f, total, &state);
    }
}

/* process_command_line()
 *
 * raw: pointer to raw input string
 * f: command line flags
 * total: current running total
 * state: pointer to current state variable
 *
 * return: the new total after this line processed
 * 
 * This is the main workhorse function. Calls get_number to process
 * a repetition prefix (e.g. "1000: ..."). Calls makeSet to process
 * a dice set (e.g. "3d6"). Calls rollset to roll the dice.
 */
int process_command_line(char *raw, flags f, int total, int *state)
{
    char *input, *rewind;
    bool error = false;

    // some preprocessing
    remove_whitespace(raw);
    int num_repetitions = get_number(raw, &rewind);

    for (int i = 0; i < num_repetitions; i++)
    {
        // the input pointer is moved through the string as it's processed
        // "rewind" saves the beginning point so that if n>1 we can process
        // the string again
        input = rewind;

        // string is processed one character at a time
        // note input[0] is equivalent to *input
        while (input != NULL && input[0] != '\0')
        {
            // process state changes
            if (input[0] == 'c' || input[0] == 'C')
            {
                total = 0;
                *state = CLR;
                input++;
            }
            else if (input[0] == '+')
            {
                if (f.verbose)
                    printf("+ ");
                *state = ADD;
                input++;
            }
            else if (input[0] == '-')
            {
                if (f.verbose)
                    printf("- ");
                *state = SUB;
                input++;
            }
            else if (input[0] == '*')
            {
                if (f.verbose)
                    printf("* ");
                *state = MUL;
                input++;
            }
            else if (input[0] == '/')
            {
                if (f.verbose)
                    printf("/ ");
                *state = DIV;
                input++;
            }
            else if (input[0] == '=')
            {
                if (f.verbose)
                    printf("==============\n");
                printf("%d\n", total);
                if (f.verbose)
                    printf("\n");
                *state = CLR;
                input++;
            }
            else if (input[0] == ' ' || input[0] == '\t')
            { // ignore whitespace
            }
            else
            { // process dice set and move the string pointer forwards
                char *left;
                diceset d = makeSet(input, &left);
                input = left;

                if (d.sides >= 0 && d.num > 0)
                { // roll the dice if it's a good dice set
                    error = false;
                    int result = rollset(d, f);
                    if (*state == ADD)
                    {
                        total += result;
                    }
                    else if (*state == SUB)
                    {
                        total -= result;
                    }
                    else if (*state == MUL)
                    {
                        total *= result;
                    }
                    else if (*state == DIV)
                    {
                        total /= result;
                    }
                    else if (*state == CLR)
                    {
                        total = result;
                    }
                    *state = CLR;
                }
                else
                { // flag an error if bad dice set
                    if (!error)
                        printf("\n{ERROR near '%s'}\n", input);
                    input++;
                    error = true;
                }
            } // else if chain
        }     // while
    }         // for
    return total;
}

// state constants for get_number
#define SKIP_LEADING_WS     1
#define READ                2
#define SKIP_TRAILING_WS    3

/* get_number
 * 
 * s: pointer to the current input string
 * pos: pointer to pointer to the rest of the string after
 * the iteration prefix is read.
 * 
 * return: number of iterations (default 1)
 * 
 * If s has an iteration prefix (e.g. "1000: ..."), reads it
 * and advances *pos so that it points to the first character
 * after the prefix.
 * */
int get_number(char *s, char **pos)
{
    // is there an iteration prefix?
    *pos = strchr(s, ':');
    if (*pos == NULL)
    {
        *pos = s;
        return 1;
    }

    // process iteration prefix
    int state = SKIP_LEADING_WS; 
    int num = 0;
    for (; s < *pos; s++)
    {
        if (state == SKIP_LEADING_WS)
        { // skip leading whitespace
            if (*s >= '0' && *s <= '9')
            {
                num = num * 10 + (*s - '0');
                state = READ; 
            }
            else if (*s == ' ' || *s == '\t')
            { // skip whitespace
            }
            else
            { // something went wrong
                return 0;
            }
        }
        else if (state == READ)
        { // read the number
            if (*s >= '0' && *s <= '9')
            {
                num = num * 10 + (*s - '0');
                state = READ;
            }
            else if (*s == ' ' || *s == '\t')
            {   // end of number
                state = SKIP_TRAILING_WS;
            }
            else
            { // something went wrong
                return 0;
            }
        }
        else if (state == SKIP_TRAILING_WS)
        { // skip trailing whitespace
            if (*s != ' ' && *s != '\t')
            { // something went wrong
                return 0;
            }
        }
    }
    *pos = *pos + 1;
    return num;
}

void process_one_command(char *raw, flags f) {
    int state = ADD;
    process_command_line(raw, f, 0, &state);
}