typedef struct {
    int num; 
    int sides;
} diceset;

diceset makeSet(char *diceset_string, char **remaining); 
int rollset(diceset d, flags f); 
