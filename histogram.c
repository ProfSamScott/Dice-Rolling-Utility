#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void show_help(void);

int main(int argc, char **argv)
{
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
    if (verbose)
        printf("---------------------\n     total:%10ld\n", sum);
    free(histo);
}

void show_help(void) {
puts("Usage: histogram [OPTION]...");
    puts("");
    puts("Computes a histogram from integers read from stdin.");

    puts("Command line options:");
    puts("  -h, --help,              Get help.");
    puts("  -v,                      Verbose output.");
}