void dialog(flags f);

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define CLR 4

int remove_whitespace(char *s); 
int process_command_line(char *raw, flags f, int total, int *state);
