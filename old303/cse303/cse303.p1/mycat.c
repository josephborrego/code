#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include "support.h"
//cat file
void catfile(char* file)
{
    FILE* fp;
    //file ! exist
    if(file == NULL)
    {
        fp = stdin;
    }
    else
    {
        fp = fopen(file, "r");
        //if file pointer !exist
        if(fp == NULL)
        {
            fprintf(stderr, "Error with file\n");
            exit(0);
        }
    }
    //print characters in file till end
    char ch;
    //size_t s = 0;
    while((ch = fgetc(fp)) != EOF)
    {
        fprintf(stdout, "%c", ch);
    }
    fclose(fp);
}
//helper message
void helper(char* pro)
{
    fprintf(stdout, "Used %s file\n", pro);
    fprintf(stdout, "print contents to stdout\n");
    fprintf(stdout, "no file read stdin\n");
}
//main
int main(int argc, char** argv)
{
    long op;
    //name check
    check_student(argv[0]);
    //parse com lin
    while((op = getopt(argc, argv,"h")) != -1)
    {
        switch(op)
        {
            case 'h':helper(argv[0]);
            break;
        }
 }
    //fua = first unparsed argument
    //file name if options remain
    //if fua < argc then it passes to catfile
    catfile(optind < argc ? argv[optind] : NULL);
}


