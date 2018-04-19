#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "support.h"
//grep file
void grep_file(char* filename, char* searchstr)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        fprintf(stderr, "error with file\n");
        exit(1);
    }
    size_t s = 1025;
    char buff[s];
    while(fgets(buff, s, fp))
    {
        if(strstr(buff, searchstr))
        {
            fprintf(stdout, "%s", buff);
        }
    }
}
//helper message
void help(char* progname)
{
    fprintf(stdout, "used: %s file\n", progname);
    fprintf(stdout, "print contents of file that contain string\n");
    fprintf(stdout, "no file then read stdin\n");
}
//main
//parse arguments with enough command line options
int main(int argc, char** argv)
{
    long op;
    //name check
    check_student(argv[0]);
    //did user type h?
    while((op = getopt(argc, argv, "h")) != -1)
    {
        switch(op)
        {
            case 'h': help(argv[0]);break;
        }
    }
    //two param
    if(optind != argc - 2)
    {
        fprintf(stderr, "not enough arguments\n");
        exit(1);
    }
    grep_file(argv[optind + 1], argv[optind]);

}
