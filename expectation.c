/* A simple utility to read a histogram and compute the expectation
 * from it. Histogram format is two ints per line: value followed
 * by number of instances of that value (e.g. "3 10" means 10 3s)
 *
 * NOTE: For this utility, expectation could be computed directly
 * from the dice rolls without going through the histogram, but
 * for demonstration purposes I wanted one more component in my
 * pipe/filter chain.
 *
 * Sam Scott, McMaster University, 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void show_help(void);

/* Reads the command line flags, then reads a histogram from
 * stdin and writes the expectation to stdout. Exits with an
 * error code if something goes wrong.
 */
int main(int argc, char **argv)
{
    // read command line flags
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            show_help();
            exit(EXIT_SUCCESS);
        }
        else
        {
            fprintf(stderr,"Bad Option: '%s'. See 'expectation --help'.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    // compute the expectation from a histogram in stdin
    long value, instances;
    long sum = 0, n = 0;
    bool values_read = false;
    while (true)
    {
        int result = scanf("%ld %ld", &value, &instances);
        if (result == EOF)
            break;
        values_read = true;
        sum += instances * value;
        n += instances;
    }

    // output expectation
    if (values_read)
        printf("%f\n", (double)sum / n);
    else
        puts("No values read.");

    return EXIT_SUCCESS;
}

void show_help(void)
{
    puts("Usage: expectation [OPTION]...");
    puts("");
    puts("Computes expected value from a histogram read from stdin.");

    puts("Command line options:");
    puts("  -h, --help,   Get help.");
}
