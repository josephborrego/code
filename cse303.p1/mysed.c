#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"
#include <unistd.h>

/*
 * sed_file() - modify lines of filename based on pattern, and print result
 *              to STDOUT
 */
void sed_file(char *filename, char *pattern) {
    /* TODO: Complete this function */


  FILE* file;

  if (filename == NULL){
    perror("Cannot open file");
    exit(0);
   }
   else{
    file = fopen(filename, "r");
   }
    
  
  char command[strlen(pattern)][1024] ;
  char *tok ;
  
  tok = strtok(pattern, "/");

  int i = 0;
  while (! (tok == NULL)){
    strcpy(command[i],tok);
    i++;
    strtok(NULL, "/");
  }

  //  if ( !((command[0] == "s")&&(command[3]== "g") &&  (strlen(command[1]) > 0))){
  if (!(strlen(command[1]) > 0)){
    perror ("Invalid command");
    exit(0);
  }

  
  char line[1024];
  //  char new_line[1024];
  //  FILE *out = stdout;

  

  while (!(feof(file))){
    fgets(line, 1024, file);
    // char *currentword[1024];
 
    if (strstr(line, command[1])){
      char* part = strtok(line, command[2]);
      char rest_of_string[1024];
      int index = 0;
      int k = 0;

      
      
      printf("%s ", part);
      printf("%s ",command[2]);
       index = strstr(line, command[1])- line;
      //      index = (int)(strchr(line, command[2])-line);
      for (k = 0; k < 1024; k++){
	rest_of_string[k] = line [1024-index];
      }
      printf(rest_of_string);
    }
      
    else {
      write(1, line, 1024);
      break;
    }

  }  
  
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the contents of FILE to STDOUT\n");
    printf("With no FILE, read standard input\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    char* filename=NULL;
    char* pattern=NULL;
    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "hsf:")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
	  case 's': pattern = optarg; break;
	  case 'f': filename = optarg; break;
        }
    }

    /* TODO: fix this invocation */
    sed_file(filename, pattern);
}
