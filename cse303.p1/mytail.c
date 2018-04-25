#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include <string.h>

/*
 * tail_file() - display the last numlines lines of a file or stdin
 */
void tail_file(char *filename, int numlines) {
  /* TODO: Complete this function */
 
  FILE *file;
  char lines_to_read[numlines+1][1024];
  char lines_to_print[numlines][1024];
  int i =0;
  int j = 0;
  int k = 0;
  
  if (!(filename == NULL)){
    file = fopen(filename, "r");
    if (file == NULL){
      perror("Error opening file");
      exit(0);
    }

  }
  else{
    file = stdin;
  }

   while (!(feof(file))){
     for (i = 0; i <=  numlines; i++){
      fgets(lines_to_read[i], 1024, file);
     }
   }

   for(j=1; j <= numlines; j++){
     strcpy(lines_to_print[j-1],lines_to_read[j]);
   }

   for (k=0; k < numlines; k++){
     printf(lines_to_print[k]);
   }
   
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the last 10 lines  of FILE to STDOUT\n");
    printf("With no FILE, read from STDIN\n");
    printf("  -nK    print the last K lines instead of the last 10\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    int numlines = 10;

    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage, */
    /* and the parametered 'n' option, for getting the number of lines. */
    /* TODO: parse the arguments correctly */
    while ((opt = getopt(argc, argv, "hn:")) != -1) {
        switch(opt) {
	case 'h': help(argv[0]);break;
	case 'n': numlines = atoi(optarg);  break;
	  
        }
    }

    //    printf("%d" , numlines);
    /* TODO: fix this invocation */
    tail_file((optind < argc ? argv[optind] : NULL), numlines);
}
