#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "parser.h"
#include "diceio.h"

bool test_makeSet(int tc, char *s, int num, int sides, char *expected_remaining) {
    diceset d;
    char *remaining;
    d = makeSet(s, &remaining);
    if (d.num != num || d.sides != sides || strcmp(remaining, expected_remaining) != 0) {
        printf("TC %d FAILED.\n   Result: %d, %d, %s\n Expected: %d, %d, %s\n", tc, d.num, d.sides, remaining, num, sides, expected_remaining);
        return false;
    }
    return true;
}

int main(void) {
    bool success = true;

    // testing the parser
    int tc = 1;
    success = success && test_makeSet(tc++, "3d6", 3, 6, "");
    success = success && test_makeSet(tc++, "d6", 1, 6, "");
    success = success && test_makeSet(tc++, "3d6-5", 3, 6, "-5");
    success = success && test_makeSet(tc++, "100*2", 100, 0, "*2");
    success = success && test_makeSet(tc++, "fdjskl", -1, -1, "fdjskl");

    // final output
    if (success) {
        puts("All tests successful");
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
