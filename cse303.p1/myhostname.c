#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "support.h"

#include <string.h>

#include <unistd.h>

/*
 * host() - Print the hostname of the machine on which this program is
 *          running, formatted a few different ways
 */
void host(void) {
    /* TODO: Complete this function */
  
  char lowercase_host [255];
  char uppercase_host [255];
  char alternating_host [255];
  char reversed_host [255];
  gethostname(lowercase_host,255);

  strcpy(alternating_host, lowercase_host);
  
  int i = 0;
  int j = 0;
  int k = strlen(lowercase_host)-1;
  
  while (i <= strlen(lowercase_host)){
    uppercase_host[i] = toupper(lowercase_host[i]);
    if (i%2 == 0){
      alternating_host[i] = toupper(lowercase_host[i]);
    }
    else{
      alternating_host[i] = lowercase_host[i];
    }

    i++;
  }


  while ( (j <= strlen(lowercase_host) - 1) && (k >= 0)){
    reversed_host[j]= lowercase_host[k];
    j++;
    k--;
  }
    
  printf(lowercase_host);
  printf("\n");
  printf(uppercase_host);
  printf("\n");
  printf(alternating_host);
  printf("\n");
  printf(reversed_host);
  printf("\n");

}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Display the hostname of the machine\n");
    printf("The name will be displayed four ways, in the following order, on "
           "four lines:\n");
    printf("  all lowercase\n");
    printf("  ALL UPPERCASE\n");
    printf("  mIxEd LoWeRaNdUpPeR\n");
    printf("  emantsoh (i.e., reversed)\n");
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

    /* no need to look at arguments before calling the code */
    host();
}
