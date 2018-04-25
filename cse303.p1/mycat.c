#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * cat_file() - display the contents of a file by reading it, line by line
 */
void cat_file(char *filename) {
    /* TODO: Complete this function */

  FILE *file;
  char line [1024];

  if(!(filename == NULL)){
    
    file = fopen (filename, "r");

  
    if (file == NULL){
      perror ("Error Opening File: Filename is not valid");
      exit(0);
    }
  
    while (!(feof (file))){
      fgets (line, 1024, file);
      if (!(feof (file))){
	if (!(line == NULL)){
	  printf (line);
	  printf ("\n");
	}
      }
    }
  }
  
  else{
    file = stdin;

    while (!(feof(file))){
      fgets (line, 1024, file);
      if(!(line == NULL)){
	printf(line);
	printf("\n");
      }
    }
  }
	  
    fclose(file);
 }

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the contents of FILE to STDOUT\n");
    printf("With no FILE, read from STDIN\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* optind is a global indicating the first unparsed argument */
    /* If we have options remaining, it must mean we have a file name */
    /* Note that getopt rearranges the entries in argv */
    cat_file(optind < argc ? argv[optind] : NULL);
}
