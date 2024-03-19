/* -b (brief flag)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"
#include "parser.h"
#include "diceio.h"

flags init_flags(int argc, char **argv) {
    flags f;
    f.verbose = false;

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i],"-v") == 0) {
            f.verbose = true;
        } else {
            printf("Bad Flag: %s.\n",argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    return f;
}

int main(int argc, char **argv) {

    flags f = init_flags(argc, argv);

    if (f.verbose)
        printf("Dice Parser v0.1.0\n");

    srand(time(NULL));

    dialog(f);

    if (f.verbose)
        puts("Goodbye!");

    return EXIT_SUCCESS;
}
