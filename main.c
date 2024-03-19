/* TODO: +, -, *, / (round down), clear, total, -b (brief flag), 3d6 without + or - performs a clear operation.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"
#include "parser.h"

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

    char input[100];
    puts("Enter some dice strings!");
    do { 
        int result = scanf("%100s",input);
        if (result == EOF || input[0] == 'q' || input[0] == 'Q')
            break;
        diceset d = makeSet(input);
        if (d.sides >= 0 && d.num > 0) {
            printf("%d\n", rollset(d, f));
        } else {
            printf("ERROR! %dd%d\n",d.num,d.sides);
        }
    } while (true);

    if (f.verbose)
        puts("Goodbye!");

    return EXIT_SUCCESS;
}
