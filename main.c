/* gotta fix the spacing for repeated commands
 * -c command
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "utilities.h"
#include "parser.h"
#include "diceio.h"

int main(int argc, char **argv)
{

    srand(time(NULL));
    flags f = init_flags(argc, argv);

    if (f.verbose)
        printf("Dice Parser v0.1.0\n");

    if (f.command != NULL)
    {
        int state = ADD;
        process_command_line(f.command, f, 0, &state);
    }
    else
    {
        dialog(f);
    }

    if (f.verbose)
        puts("Goodbye!");

    return EXIT_SUCCESS;
}
