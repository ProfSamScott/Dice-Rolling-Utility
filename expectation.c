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
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            show_help();
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Bad Option: '%s'. See 'expectation --help'.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

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
    if (values_read)
        printf("%f\n", (double)sum / n);
    else
        puts("No values read.");
    return EXIT_SUCCESS;
}

void show_help(void)
{
    puts("Usage: histogram [OPTION]...");
    puts("");
    puts("Computes expected value from a histogram read from stdin.");

    puts("Command line options:");
    puts("  -h, --help,   Get help.");
}