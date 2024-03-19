#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    int size = 10;
    long num;
    long *histo = calloc(size,sizeof(long));
    if (histo == NULL) {
        puts("Memory error. Aborting.");
        exit(EXIT_FAILURE);
    }
    while (true) {
        int result = scanf("%ld",&num);
        if (result == EOF)
            break;
        if (num < size) {
            if (num >= 0)
                histo[num]++;
            else {
                free(histo);
                puts("Negative Number! Aborting");
                exit(EXIT_FAILURE);
            }
        } else {
            int newsize = num+1;
            long *newhisto = realloc(histo, newsize*sizeof(long));
            if (newhisto == NULL) {
                free(histo);
                puts("Memory error. Aborting.");
                exit(EXIT_FAILURE);
            }
            histo = newhisto;
            for (int i=size; i<newsize; i++) 
                histo[i] = 0;
            histo[num]++;
            size = newsize;
        }
    }
    long sum = 0;
    for (int i=0; i<size; i++) {
        sum += histo[i];
        if (histo[i] > 0) {
            printf("%10d:%10ld\n",i, histo[i]);
        }
    }
    printf("---------------------\n     total:%10ld\n",sum);
    free(histo);
}
