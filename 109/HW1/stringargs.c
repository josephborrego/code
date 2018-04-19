#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
	char *buffer = NULL;
	size_t  size = 0;  //if we say size_t we can use it on another machine

	int retval = getline(&buffer, &size, stdin);
	fprintf(stdout, "Return value is: %d\n", retval);
	fprintf(stdout, "Where buffer points to: '%p'\n", buffer);
	fprintf(stdout, "Getline changed size to: %d\n", size);
	fprintf(stdout, "The input is '%s'\n", buffer);
	return 0;

}
