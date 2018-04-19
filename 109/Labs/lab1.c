
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{

char *word = (char *)malloc(10 * sizeof(char)); // this the word we're going to compare

	while(1)
	{

	int value = fscanf(stdin, "%ms", word);

	if(value == -1)
	{
		if(strlen(word) <5 || strlen(word) > 5)
		{
		printf("why u no play\n");
		break;
		}
	}

	if(strlen(word) == 5)
	{
		printf("You entered a 5-letter word, was it donut\n");

		if(strcmp(word,"donut\0")==0)
		{
		printf("yes it was\n");
		exit(1);
		}
		else
		{
		printf("no it was '%s' :(\n", word);
		exit(1);
		}
	}

free(word);
word = NULL;
	} // end of while loop


}
