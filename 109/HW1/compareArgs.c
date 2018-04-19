#include<stdio.h>
#include<string.h>

#include"ourstring.h"

int main(int argc, char *argv[])
{

//size_t lengthFirst = length(argv[0]);
//fprintf(stdout, "First argument length is : %d\n", lengthFirst);

for(int i = 0; i< argc; i++)
{
	for(int j = i +1; j <argc; j++)
	{
		int compareResult= compare(argv[i], argv[j]);
		int strcmpResult = strcmp(argv[i], argv[j]);
		//strncmp is only for prefixes
		if(compareResult >= 0)
		{
			char *temp = argv[i];
			argv[i] = argv[j];
			argv[j] = temp;
		}
		if(compareResult != strcmpResult)
		{
			fprintf(stderr, "compare difference between '%s' '%s'\n", argv[i], argv[j]);
		}
	}
}


fprintf(stdout, "The sorted arguments are:\n");

	for(size_t i =0; i < argc; i++)
	{
		fprintf(stdout, "%s", argv[i]);
		if((i + 1) != argc)
		{
			fprintf(stdout, ", ");
		}

	}
	fprintf(stdout, "\n");
return 0;
}
