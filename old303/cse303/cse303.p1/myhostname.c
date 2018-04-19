#include <netdb.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include "support.h"
//host
void host()
{
    char hostname[128];
    gethostbyname(hostname);
    fprintf(stdout, "%s\n", hostname);
}
//helper
void help(char* progname)
{
    fprintf(stdout, "use %s\n", progname);
    fprintf(stdout, "show host name\n");
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


