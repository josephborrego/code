#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include "support.h"
// wc counts words, chars, lines
void wc_file(char* filename)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        fprintf(stderr, "error with file\n");
        exit(1);
    }
    int q;
    size_t bytes = 0;
    size_t wordc = 0;
    size_t linec = 0;
    size_t sp, wurd;
    sp = 0;
    wurd = 0;
    while((q = fgetc(fp)) != EOF)
    {
        //fprintf(stderr, "loop\n");
        if((q >= 'a' && q <= 'z') || (q >= 'A' && q <= 'Z') || (q >= '0' && q <= '9'))
        {
            sp = 0;
            wurd = 1;
            bytes++;
            //fprintf(stderr, "IF bytes %zu, linec %zu, wordc %zu\n", bytes, linec, wordc);
        }
        else if(q == ' ' || q =='\t')
        {
            //fprintf(stderr, "ELSE IF1 bytes %zu, linec %zu, wordc %zu\n", bytes, linec, wordc);
            if(!sp && wurd)
            {
                wordc++;
            }
            sp = 1;
            wurd = 0;
            bytes++;
        }
        else if(q == '\n')
        {
        //fprintf(stderr, "ELSEIF2 bytes %zu, linec %zu, wordc %zu\n", bytes, linec, wordc);
            if(wurd)
            {
                wordc++;
            }
            wurd = 0;
            bytes++;
            linec++;
        }
        else
		{
            sp = 0;
            bytes++;
        }
    }
    fprintf(stdout, "      %zu      %zu     %zu %s\n", linec, wordc, bytes, filename);
    fclose(fp);
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
int main(int argc, char **argv)
{
    /* for getopt */
    long opt;
    /* run a student name check */
    check_student(argv[0]);
    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1)
    {
        switch(opt)
        {
         case 'h': help(argv[0]); break;
        }
    }
    /* error if we don't have a file, else call wc_file */
    if (argc != 2)
    {
        printf("Error: no file given\n");
        exit(1);
    }
    wc_file(argv[1]);
}

