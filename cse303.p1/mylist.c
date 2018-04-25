
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"


struct node {
  int number;
  struct node *next;
};
struct node *head = NULL;

/*
 * list_task() - read from stdin, determine the appropriate behavior, and
 *               perform it.
 */

void list_task(void) {
    /* TODO: Complete this function */

  char command [4];
  FILE* file = stdin;
  struct node *current = NULL;

  while (!(feof(file))){
     fgets (command , 4, file);
      if (command[0] == 'i'){
	if (head == NULL){
	  // head->number = atoi(command[2]);
	  head->number = command[3] - '0';
	  head->next = current;
	}
	else if (current == NULL){
	  // current->number = atoi(command[2]);
	  current->number = command [3] - '0';
	  current->next = NULL;;
	}
	else{
	  // current->next->number = atoi(command[2]);
	  current->next->number = command [3] - '0';
	  current->next->next = NULL;
	}
      	  
      }
      else if (command [0] == 'r'){
      }
      else if (command [0] == 'p'){
	current = head;
	printf("%d",current->number);
	while (!(current->next == NULL)){
	  printf("-->");
	  printf ("%d", current->next->number);
	  current = current->next;
	}	
      }
      else if (command [0] == 'x'){
	exit(0);
      }
      else {
	perror ("Invalid command");
	exit(0);
      }
  }
  
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Run an interactive list manipulation program\n");
    printf("Commands: [i]insert, [r]emove, [p]rint, e[x]it\n");
    printf("  (Commands require an integer argument)\n");
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

    /*
     * parse the command-line options.  For this program, we only support the
     * parameterless 'h' option, for getting help on program usage.
     */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* run the list program */
    list_task();
}
