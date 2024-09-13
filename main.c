/* Command Line Utility for rolling dice 
 *
 * Sam Scott, McMaster University, 2024 
 * new comment
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "utilities.h"
#include "parser.h"
#include "diceio.h"

/* main()
 * 
 * processes command line arguments, initializes random number 
 * seed, and calls diceio utilities to dialog via stdin or 
 * process a single command (-c option)
 * 
 * When used in verbose mode (-v) it can be a command line tool
 * for someone to roll dice. When not in verbose mode, it can
 * pipe results to histogram.
 * 
 * e.g. dice -c "1000: 3d6 - 2 + d4 * 2d6 =" | histogram
 * 
 * Run with --help to see usage info
 */
int main(int argc, char **argv)
{
    srand(time(NULL));
    flags f = init_flags(argc, argv);

    if (f.verbose)
        printf("Dice Parser v0.1.0\n");

    if (f.command != NULL)
    {
        process_one_command(f.command, f);
    }
    else
    {
        dialog(f);
    }

    if (f.verbose)
        puts("Goodbye!");

    return EXIT_SUCCESS;
}
