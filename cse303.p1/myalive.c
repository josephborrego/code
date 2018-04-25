#include <getopt.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "support.h"
#include <unistd.h>

void sig_handler_keypress(int signum);
void sig_handler_timer(int signum);
volatile int flag = 0;

/*
 * alive() - install some signal handlers, set an alarm, and wait...
 */
void alive(void) {
  
    /* TODO: Complete this function */
    /* Note: you will probably need to implement some other functions */

  struct timeval start_time, end_time;
  int elapsed_time;
  
  signal(SIGINT, sig_handler_keypress);
  signal(SIGALRM, sig_handler_timer);

  //  flag = 0;
  
  alarm(10);
  gettimeofday(&start_time, NULL);
  //  printf("%ld", start_time.tv_sec);

  while(flag == 0){
    //    printf("d");
    signal(SIGINT, sig_handler_keypress);
  }

  gettimeofday(&end_time, NULL);
  
  // elapsed_time = ((end_time.tv_usec - start_time.tv_usec)*1000000);
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) ;
  printf ("Time elapsed: %d \n", elapsed_time);
}

void sig_handler_keypress (int signum) {

  write(1,"no", 2);
  alarm(10);

}

void sig_handler_timer(int signum){
  flag = 1;
}
  
/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Swallow SIGINT, exit on SIGALARM\n");
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
    alive();
}
