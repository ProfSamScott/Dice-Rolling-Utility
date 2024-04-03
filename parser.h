/* Public definitions for the dice parser utilities
 *
 * Sam Scott, McMaster University, 2024
 */

/* Holds a representation of a dice set (e.g. "3d6") */
typedef struct {
    int num;  
    int sides; // if 0, this is a constant (e.g. "23")
} diceset;

/* Called to make a diceset. Takes a string, returns the
 * diceset structure corresponding to the first diceset
 * found in the string, sets *remaining to point to what's
 * left in the string.
 */
diceset makeSet(char *diceset_string, char **remaining); 

/* Called to roll and add up the dice in a diceset. */
int rollset(diceset d, flags f); 
