#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[])
{

	char *chunk = (char *)malloc(80 * sizeof(char));

	fscanf(stdin, "%10s", chunk);

	fprintf(stdout, "The string is: %s\n", chunk);
	fprintf(stdout, "The string is: %s\n", &chunk[2]); //&dereference
	fprintf(stdout, "The string is: %s\n", (chunk + 2));

	int *number = (int *)chunk;
	fprintf(stdout, "Number is %x\n", *number);


	return 0;
}
