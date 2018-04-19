#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
	char *word = NULL;

	while(fscanf(stdin, "%ms", &word) == 1)
	{
		if(strlen(word) == 5)
		{
			fprintf(stdout, "You entered a 5-letter word, was it donut?\n");
			if(!strcmp(word, "donut"))
			{
				fprintf(stdout, "Yes it was\n");
			}
			else
			{
				fprintf(stdout, "No it was '%s'");
				break;
			}
		}
	}

	return 0;
}
