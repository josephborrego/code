#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "support.h"
//sed: mod file
void sed_file(char* filen, char* lin)
{
    FILE* fp = fopen(filen, "r");
    if(fp == NULL)
    {
        fprintf(stderr, "error\n");
        exit(1);
    }
    char buff[1025];
    char* look;
    char* remake;
    if(strcmp(strtok(lin, "/"), "s"))
    {
        fprintf(stderr, "first param is wrong\n");
        exit(1);
    }
    look = strtok(NULL, "/");
    if(!strcmp(look, ""))
    {
        fprintf(stderr, "first param is wrong\n");
        exit(1);
    }
    remake = strtok(NULL, "/");
    if(strcmp(strtok(NULL, "/"), "g"))
    {
        fprintf(stderr, "first param is wrong\n");
        exit(1);
    }
    if(!strcmp(remake, "g") && strtok(NULL, "/") == NULL)
    {
        remake = "";
    }
    int duh;
    //int yeah;
    char* newl;
    char* templ;
    while(fgets(buff, 1025, fp) != NULL)
    {
        templ = (char*)malloc(1025 * sizeof(char));
        strcpy(templ, buff);
        duh = (size_t) strstr(templ, look);
        while(duh)
        {
            int q = duh - (size_t)templ;
            char* d = (char *) (duh + strlen(look));
            newl = (char*)malloc((1+ strlen(templ) - strlen(look) + strlen(remake)) * sizeof(char*));
            memset(newl, 0, (1 + strlen(templ) - strlen(look) + strlen(remake)) * sizeof(char*));
			 strncpy(newl, templ, q);

            strcat(newl, look);
            strcat(newl, d);

            free(templ);
            templ = (char *)malloc((strlen(newl) + 1) * sizeof(char));

            strcpy(templ, newl);
            duh = (size_t)strstr(templ, look);

            free(newl);
        }
        fprintf(stdout, "%s", templ);
        free(templ);
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

    /* TODO: fix this invocation */
    sed_file(argv[optind+1], argv[optind]);
}

