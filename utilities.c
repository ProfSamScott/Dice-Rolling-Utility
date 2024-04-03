/* Some basic utilities
 *
 * Sam Scott, McMaster University, 2024
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "utilities.h"

void show_help();

/* remove_whitespace()
 * 
 * Removes all whitespace characters from a given string.
 */
void remove_whitespace(char *s) {
    int j = 0;
    for (int i=0; i<strlen(s); i++) {
        if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t') {
            s[j] = s[i];
            j++;
        } 
    }
    s[j] = '\0';
}

/* init_flags()
 * 
 * Reads the command line options passed to main and returns a
 * flags object that corresponds to the options found. Exits
 * on a bad command line argument.
 * 
 * This is not quite to LINUX standards (e.g. -c"3d6" won't work)
 */
flags init_flags(int argc, char **argv) {
    flags f;
    f.verbose = false;
    f.command = NULL;

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i],"-v") == 0) {
            f.verbose = true;
        } else if (strcmp(argv[i],"-c") == 0) {
            i = i + 1;
            if (i == argc) {
                printf("Incorrect Usage: '-c'. See 'dice --help'.\n");
                exit(EXIT_FAILURE);
            }
            f.command = argv[i];
        } else if (strcmp(argv[i],"--help") == 0 || strcmp(argv[i],"-h") == 0) {
            show_help();
            exit(EXIT_SUCCESS);
        } else {
            printf("Bad Option: '%s'. See 'dice --help'.\n",argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    return f;
}

/* show_help()
 */
void show_help() {
    puts("Usage: dice [OPTION]...");
    puts("");
    puts("Simulates the rolling of dice using commands from stdin.\n   Dice sets are specified by '#d#' format, where # indicate number of dice (optional) and number of sides per die.");
    puts("  Example: '2d6' rolls two six-sided dice and adds the rolls together.");
    puts("");
    puts("  Supports constants, *, +, -, and / (rounded down).\n   Use = to get the final result.");
    puts("  Example: '2d6 * d4 + 5 =' rolls 2d6, then multiplies by d4, then adds 5 and displays the result.");
    puts("");
    puts("  Single line commands can be repeated by prefixing with '#:'");
    puts("  Example: '1000: 3d8 - 4 =' repeats '3d8 - 4 =' one thousand times.");
    puts("");
    puts("  Use 'c' to clear the buffer.");
    puts("  Example: '2d6 c 3d8 + 5=' rolls 2d6, then clears, rolls 3d8, adds 5, and displays the result.");
    puts("");
    puts("  Use 'q' to quit.");
    puts("");
    puts("Command line options:");
    puts("  -c \"command_string\",     Rolls the command string once and exits.");
    puts("  -h, --help,              Get help.");
    puts("  -v,                      Verbose output.");
}