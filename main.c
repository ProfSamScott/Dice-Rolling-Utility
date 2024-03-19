#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"
#include "parser.h"

flags init_flags() {
    flags f;
    f.verbose = false;
    return f;
}

int main(int argc, char **argv) {
	printf("Dice Parser v0.1.0\n");

    flags f = init_flags();

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i],"-v") == 0) {
            f.verbose = true;
        } else {
            printf("Bad Flag: %s.\n",argv[i]);
            return EXIT_FAILURE;
        }
    }

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

    puts("Goodbye!");
    return EXIT_SUCCESS;
}
