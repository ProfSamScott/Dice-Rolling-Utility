#include <stdbool.h>

/* Structure holds the results of parsing the command line arguments */
typedef struct {
    bool verbose;
    char *command;
} flags;

/* removes whitespace from s*/
void remove_whitespace(char *s); 

/* reads and interprets command line arguments*/
flags init_flags(int argc, char **argv);