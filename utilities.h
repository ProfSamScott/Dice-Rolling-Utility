#include <stdbool.h>

typedef struct {
    bool verbose;
    char *command;
} flags;

int remove_whitespace(char *s); 
flags init_flags(int argc, char **argv);