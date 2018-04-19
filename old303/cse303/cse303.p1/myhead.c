#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include "support.h"
//head
void head_file(int numlines)
{
    size_t size = 1025;
    char str[size];
    int count = 0;
    while(fgets(str, size, stdin) && (count < numlines))
    {
        fprintf(stdout, "%s", str);
        count++;
    }
}
//helper message
void help(char* progname)
{
    fprintf(stdout, "used %s\n", progname);
    fprintf(stdout, "print lines\n");
}
int main(int argc, char **argv)
{
    // for getopt 
    long opt;
    int numlines = 10; // default number of lines

    // run a student name check
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

