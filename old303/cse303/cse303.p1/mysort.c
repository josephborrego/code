#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "support.h"

int comp(const void* uno, const void* dos)
{
    const char** first = (const char**)uno;
    const char** second = (const char**)dos;
    return strcmp(*first, *second);
}

//sort file
// read, sort, output
// booleans are used to determine sortness and output
void sort_file(char* filename, int unique, int reverse)
{
int maxlines = 1000000, linesize = 1024;
    char ** buffer = (char **) malloc(maxlines * sizeof(char *));
    FILE * fp = fopen(filename, "r");
    if (fp == NULL)
	{
        perror("There was an error opening a file");
        exit(1);
    }
    int i = 0, j = 0;
    char ch;
    while(i < maxlines && (ch = fgetc(fp)) != -1)
	{
        if (ch == '\n')
		{
            buffer[i] = (char *) malloc(linesize * sizeof(char));
            i++;
        }
    }
    fseek(fp, 0, SEEK_SET);
    while (fgets(buffer[j], linesize, fp))
	{
        //fprintf(stdout, buffer[j]);
        j++;
    }
    fclose(fp);
    qsort(buffer, (size_t) i, sizeof(char *), comp);
    j = 0;
    if (unique && !reverse)
	{
        while (j < i)
		{
            int l = 0, unique = 1;
            while (l < j && unique)
			{
                if (strcmp(buffer[j], buffer[l]) == 0)
				{
                    unique = 0;
                }
                l++;
            }
			if (unique)
			{
                printf("%s", buffer[j]);
            }
			j++;
        }
    }
	else if (reverse && !unique)
	{
        j = i - 1;
        while (j >= 0)
		{
            printf("%s", buffer[j]); //afvnjfsnv
            j--;
        }
    }
	else if (reverse && unique)
	{
        j = i - 1;
        while (j >= 0)
		{
            int l = i - 1, unique = 1;
            while (l > j && unique)
			{
                if (strcmp(buffer[j], buffer[l]) == 0)
				{
                    unique = 0;
                }
                l--;
            }
            if (unique)
			{
                printf("%s", buffer[j]);
            }
            j--;
  		} //danvjdnbvjdsbnjdfnbjdfbndfjnfdjvnfjv
    }
	else
	{
        while(j < i)
		{
            printf("%s", buffer[j]);
            j++;
        }
    }
    int k = 0;
    while(k < i)
	{
        free(buffer[k]);
        k++;
    }
    free(buffer);
}
/*
 * help() - Print a help message.
 */
void help(char *progname)
{
    printf("Usage: %s [OPTIONS] FILE\n", progname);
    printf("Sort the lines of FILE and print them to STDOUT\n");
    printf("  -r    sort in reverse\n");
    printf("  -u    only print unique lines\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char** argv)
{
 /* for getopt */
    long opt;
    /* ensure the student name is filled out */
    check_student(argv[0]);
    /* parse the command-line options.  They are 'r' for reversing the */
    /* output, and 'u' for only printing unique strings.  'h' is also */
    /* supported. */
    /* TODO: parse the arguments correctly */
    while ((opt = getopt(argc, argv, "hur")) != -1) {
        switch(opt) {
        case 'h': help(argv[0]); break;
        case 'u':  break;
        case 'r':  break;
        }
    }
    /* TODO: fix this invocation */
    sort_file(argv[optind], 0, 0);
}


