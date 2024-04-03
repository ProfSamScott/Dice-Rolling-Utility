/* Public functions and constants for basic dice i/o 
 *
 * Sam Scott, McMaster University, 2024
 */

/*
 * Called with command line flags f to dialog with the user
 */
void dialog(flags f);

/* Called if -c flag used to process a single line (*raw). 
 * Command line flags passed as f.
 */
void process_one_command(char *raw, flags f);
