/* A simple utility to read a list of int values from stdin and
 * produce a histogram. Good example of calloc and realloc in action.
 *
 * Can be used in verbose mode for viewing output. Otherwise, suitable
 * for piping to expectation.
 *
 * Sam Scott, McMaster University, 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void show_help(void);

/* Reads the command line flags, then reads integers from
 * stdin and writes a histogram to stdout. Exits with an
 * error code if something goes wrong.
 */
int main(int argc, char **argv)
{
    // read command line flags
    bool verbose = false;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            verbose = true;
        }
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            show_help();
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Bad Option: '%s'. See 'histogram --help'.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    // compute the histogram (initial size 10, grows as necessary)
    int size = 10;
    long num;
    long *histo = calloc(size, sizeof(long));
    if (histo == NULL)
    {
        puts("Memory error. Aborting.");
        exit(EXIT_FAILURE);
    }
    while (true)
    {
        int result = scanf("%ld", &num);
        if (result == EOF)
            break;
        if (num < size)
        {
            if (num >= 0)
                histo[num]++;
            else
            {
                free(histo);
                puts("Negative Number! Aborting");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            int newsize = num + 1;
            long *newhisto = realloc(histo, newsize * sizeof(long));
            if (newhisto == NULL)
            {
                free(histo);
                puts("Memory error. Aborting.");
                exit(EXIT_FAILURE);
            }
            histo = newhisto;
            for (int i = size; i < newsize; i++)
                histo[i] = 0;
            histo[num]++;
            size = newsize;
        }
    }
    long sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += histo[i];
        if (histo[i] > 0)
        {
            if (verbose)
                printf("%10d:%10ld\n", i, histo[i]);
            else
                printf("%d %ld\n", i, histo[i]);
        }
    }

    // output result
    if (verbose)
        printf("---------------------\n     total:%10ld\n", sum);
    free(histo);

    return EXIT_SUCCESS;
}

void show_help(void)
{
    puts("Usage: histogram [OPTION]...");
    puts("");
    puts("Computes a histogram from integers read from stdin.");

    puts("Command line options:");
    puts("  -h, --help,   Get help.");
    puts("  -v,           Verbose output.");
}