#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

size_t length(char *word);
int compare(char *first, char *second);



int main(int argc, char **argv)
{
	char *buffer = NULL;
	size_t  size = 0;  //if we say size_t we can use it on another machine
	int areWeDone = 0;

	FILE *input = stdin;
	char *filename = NULL;

	int nextArg = 1;



	while(nextArg < argc)
	{
		char *currentArg = argv[nextArg];
		nextArg++;


// argc
		if(nextArg >= argc)
		{
			break;
		}

		if((currentArg[0] == '-' && (currentArg[1] == 'f') && (currentArg[2] == '\0'))
		{
			 filename = argv[nextArg];
			nextArg++;
		}
	}



// END OF PROCESSING COMMAND LINE ARGUMENTS


//if (filename != NULL)
if (filename)
{

	input = fopen(filename, "r");
	if(input == NULL)
	{
		int error = errno;
		fprintf(stderr, "Error trying to open file '%s'\n", filename);
		fprintf(stderr, "Error(%d): %s\n", error, strerror(error));
		return error;
	}
}

char **lines = (char **)malloc(80 * sizeof(char *));
int lineCapactity = 80;
int lineSize = 0;


//fgetc version
//start of real code
// method to read in lines of text
int stop = 0;
	while(!stop)
	{
		char *storage = (char *)malloc(80 * sizeof(char));
		int capacity = 80;
		int size = 0;

		int stop = 0;
		while(1)
		{
			int nextLetterRetval = fgetc(input);
			unsigned char nextLetter = (unsigned char)fgetc(input);

			fprintf(stderr, "Recieved %d\n", (int)nextLetter);

			if(nextLetter == EOF)
			{
				fprintf(stderr, "Got an EOF, uhoh! :(\n");
				stop = 1;
				break;
				// End of input of error case
			}
			if(nextLetter == '\n')
			{
				break;
			}
			if(size == capacity)
			{
				//reassign storage
				char *temp = (char *)malloc(capacity * 2 * sizeof(char));
				for(int i = 0; i < size; i++)
				{
					temp[i] = storage[i];
				}

				capacity *= 2;
				free(storage);
				storage = temp;

				}

			storage[size] = nextLetter;
			size++;

			}
			}
			storage[size] = '\0';
//			fprintf(stdout, "User entered '%s'\n'", storage);
//			fprintf(stdout, "Length Real %d, Length Ours %d \n", strlen(storage)
//			free(storage);
//			storage = NULL;
	lines[lineSize] = storage;
	lineSize++;
	}


	// while(!areWeDone)
	while(areWeDone == 0)
	{
		int retval = getline(&buffer, &size, stdin);

		if(retval == -1)
		{
				areWeDone = 1;
		}
		if(retval > 0)
		{
		int location = retval - 1;
	//	location = strlen(buffer);
	//	fprintf(stdout, "Strlen detected %d\n", location);
			if(buffer[location] == '\n')
			{
				buffer[location] = '\0';
			}

		}

		fprintf(stdout, "Return value is: %d\n", retval);
		fprintf(stdout, "Where buffer points to: '%p'\n", buffer);
		fprintf(stdout, "Getline changed size to: %d\n", size);
		fprintf(stdout, "The input is '%s'\n", buffer);

		free(buffer);
		buffer = NULL; //set it to to null to allocate the memory
	}


	return 0;

}

//g++ -o p2 stringargs.c 
// redirect
// ./p2 < temp
// redirects what's in temp as the input of temp

size_t length(char *word);
{
	size_t retval = 0;

	int location = 0;
	while(*(word + location) != '\0')
	//while(word[location] != '\0')
	{
		retval++; // could use retval to handle both instances
		location++;
	}

	return retval;

}
int compare(char *first, char *second); 
{
	size_t sizeFirst = length(first);
	size_t sizeSecond = length(second);

	size_t loopMax = sizeFirst;

	if(sizeSecond < loopMax)
	{
		loopMax = sizeSecond;
	}

	for(size_t i = 0; i <loopMax; i++)
	{
		int diff = first[i] - second[i];
			if(diff != 0)
			{
				return diff;
			}
	}

	if(sizeFirst == sizeSecond)
	{
		return 0;
	}

	if(sizeFirst > sizeSecond)
	{
		return first[loopMax];
	}

	return -1 * second[loopMax];

}



