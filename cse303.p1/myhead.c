#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * head_file() - display the first numlines lines of stdin
 */
void head_file(int numlines) {
    /* TODO: Complete this function */
  int lines_to_read = 0;
  int lines_already_read = 0;
  char line [1024];
  
  if (numlines == 0){
    lines_to_read = 10;
  }
  else{
    lines_to_read = numlines;
  }

  FILE *file = stdin;

  while (!(feof(file))){
    if (lines_already_read < lines_to_read){
	fgets (line, 1024, file);
	if(!(line == NULL)){
	  printf(line);
	  printf("\n");
	  lines_already_read++;
	}
	
    }
    else{
      break;
    }
  }
  fclose(file);
    
}


/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [OPTION]\n", progname);
    printf("Print the first 10 lines of STDIN\n");
    printf("  -nK    print the first K lines instead of the first 10\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    int numlines = 10; /* default number of lines */

    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage, */
    /* and the parametered 'n' option, for getting the number of lines. */
    while ((opt = getopt(argc, argv, "hn:")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
          case 'n': numlines = atoi(optarg); break;
        }
    }

    /* no need for error checking here */
    head_file(numlines);
}
