#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

/*
 * grep_file() - display all lines of filename that contain searchstr
 */
void grep_file(char *filename, char *searchstr) {
    /* TODO: Complete this function */

  if (filename == NULL){
    perror("Cannot open file");
    exit(1);
  }
  else{
    FILE* file = fopen(filename, "r");

    char line_being_read[1024];

    while (!(feof(file))){
      fgets(line_being_read, 1024, file);
      if (strstr(line_being_read, searchstr)){
	printf(line_being_read);
      }
    }
}
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s STR FILE\n", progname);
    printf("Print to STDOUT the lines of FILE that contain STR\n");
    printf("With no FILE, read standard input\n");
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

    /* make sure we have two more parameters */
    if (optind != argc - 2) {
        printf("Error: not enough arguments\n");
        exit(1);
    }

    /* TODO: fix this invocation */
    //    grep_file((optind < argc ? argv[optind] : NULL), "it");
}
