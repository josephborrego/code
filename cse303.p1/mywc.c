#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * wc_file() - count characters, words, and lines
 */
void wc_file(char *filename) {
    /* TODO: Complete this function */

  FILE *file;
  //  char line [1024];
  char currentchar = ' ';
  int wordcount = 0;
  int charcount = 0;
  int linecount = 0;

  if(!(filename == NULL)){

    file = fopen (filename, "r");


    if (file == NULL){
      perror ("Error Opening File: Filename is not valid");
      exit(0);
    }

    while (!(feof (file))){
      currentchar = getc (file);
      if (currentchar == '\n'){
	linecount++;
      }
      else if (currentchar == ' '){
	wordcount++;
      }
      else {
	if ((!(currentchar == '.')) && (!(currentchar == '\t'))){
	  charcount++;
	}
      }
      
    }
    
    printf ("%d %d %d %s",linecount, wordcount, charcount, filename);
    printf ("\n");
    
  }
}
  

  
  


/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print newline, word, and byte counts for FILE\n");
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

    /* error if we don't have a file, else call wc_file */
    if (argc != 2) {
        printf("Error: no file given\n");
        exit(1);
    }
    wc_file(argv[1]);
}
