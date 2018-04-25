#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "support.h"

int comparator (const void *line1, const void *line2);

/*
 * sort_file() - read a file, sort its lines, and output them.  reverse and
 *               unique parameters are booleans to affect how the lines are
 *               sorted, and which lines are output.
 */
void sort_file(char *filename, int unique, int reverse) {
    /* TODO: Complete this function */
    /* Note: you will probably need to implement some other functions */
  
  FILE *file;
  char file_lines [1000000000][1024];
  int i = 0;
  
  if (!(filename == NULL)){
    file = fopen(filename, "r");
  }
  else{
    perror ("No filename given");
    exit(0);
  }

  for (i = 0; i < 1000000000; i++){
    fgets(file_lines[i], 1024, file);
  }

  qsort(file_lines, 1000000000, sizeof(char), comparator);

  if (!(unique == 0)){
    int j = 0;
    int l = 0;
    int m = 0;
    for (j = 0; j < 1000000000; j++){
      for (l = 0; l < 1000000000; l++){
	if (strcmp(file_lines[j],file_lines[l]) == 0){
	  // file_lines[l] == '\0';
	  for (m = l; m < 1000000000; m++){
	    strcpy(file_lines[m+1], file_lines[m]);
	  }
	
	}
      }
    }
  }
  if(!(reverse == 0)){
    char temp[1000000000][1024];
    int g = 0;

    for (g = 0; g < 1000000000 ; g++){
      strcpy (temp[g], file_lines[g]);
      //  temp[g] = file_lines[g];
      
    }
    for ( g = 0; g < 1000000000 ; g++){
      strcpy (file_lines[g], temp[1000000000-g]);
      // file_lines[g] = temp[1000000000-g];
    }
  }

  int r = 0;
  for (r = 0; r < 1000000000; r++){
    printf(file_lines[r]);
  }



  
  
}

int comparator (const void * line1, const void *line2){

  const char *c1 = line1;
  const char *c2 = line2;

  return strcmp(c1,c2);
}

 

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [OPTIONS] FILE\n", progname);
    printf("Sort the lines of FILE and print them to STDOUT\n");
    printf("  -r    sort in reverse\n");
    printf("  -u    only print unique lines\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    /* ensure the student name is filled out */
    check_student(argv[0]);

    /* parse the command-line options.  They are 'r' for reversing the */
    /* output, and 'u' for only printing unique strings.  'h' is also */
    /* supported. */
    /* TODO: parse the arguments correctly */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* TODO: fix this invocation */
    sort_file(argv[optind], 0, 0);
}
