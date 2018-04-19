#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * tail_file() - display the last numlines lines of a file or stdin
 */
void tail_file(char *filename, int numlines)
{
  /* TODO: Complete this function */
    FILE * fp;
//  printf("file is %s\n", filename);
    size_t size = 1024;
    //int point;
    int ch;
    int charcount = 0;
    int linecount = 0;
    if (filename == NULL)
    {
        char buff[256];
        memset(buff, 0, 256);
        char* lastlines[256];
        int cnter = 0;
        for(int i =0; i < numlines; i++)
        {
            lastlines[i] = malloc(size * sizeof(char));
        }
        while(fgets(buff, size, stdin) && cnter < numlines)
        {
            strcpy(lastlines[cnter], buff);
            cnter++;
            fprintf(stdout, "counter is %d\n", cnter);
        }
        printf("check check %s\n",lastlines[0]);
        cnter++;
        for(int j = numlines - cnter; j < numlines; j++)
        {
            fprintf(stdout, "%s\n", lastlines[j]);
        }
        exit(1);
    }
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        //perror("There was an error opening the file");
        fprintf(stderr, "error opening file\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
//   int po = fseek(fp, -1, SEEK_CUR);
    int start = ftell(fp);
	while (linecount <= numlines && charcount < start - 1)
    {
        //fprintf(stderr, "while 1\n");
        ch = fgetc(fp);
  //      po = fseek(fp, -2, SEEK_CUR);
        if (ch == '\n')
        {
            //fprintf(stderr, "if 1\n");
            linecount++;
            fprintf(stdout, "linec is %d\n", linecount);
        }
        charcount++;
        if (charcount == start - 1)
        {
            //fprintf(stderr, "if 2\n");
            charcount++;
        }
        //fprintf(stderr, "ooh\n");
    }
    size_t flashpoint;
    if (charcount == start)
    {
        flashpoint = -1 * charcount - 1;
    }
    else
    {
        flashpoint = -1 * charcount + 1;
    }
    fseek(fp, flashpoint, SEEK_END);
    char* hold = (char*)malloc(charcount * sizeof(char));
    size_t counter = 0;
    char c;
    while((c = fgetc(fp)) != EOF)
    {
        //fprintf(stderr, "while 2\n");
        hold[counter] = c;
        counter++;
    }
    hold[counter] = '\0';
    fprintf(stdout, "%s", hold);
    fclose(fp);
    free(hold);
}

/*
 * help() - Print a help message.
 */
void help(char *progname)
{
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the last 10 lines  of FILE to STDOUT\n");
    printf("With no FILE, read from STDIN\n");
	 printf("  -nK    print the last K lines instead of the last 10\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv)
{
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
            case 'h': help(argv[0]); break;
            case 'n': numlines = atoi(optarg); break;
        }
    }
    //fprintf(stdout, "numlines is %d", numlines);
    //exit(1);
    /* TODO: fix this invocation */
    tail_file(optind < argc ? argv[optind] : NULL, numlines);
}

