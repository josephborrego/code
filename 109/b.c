#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

size_t length(char *word);
int compare(char *first, char *second);

int main(int argc, char **argv)
{
	char *buffer = NULL;
	size_t size = 0;

	FILE *input = stdin;
	char *filename = NULL;

	int nextArg = 1;
	while(nextArg < argc)
	{
		char *currentArg = argv[nextArg];
		nextArg++;

		if(nextArg >= argc)
		{
			break;
		}

		if((currentArg[0] == '-') && (currentArg[1] == 'f') &&
			(currentArg[2] == '\0'))
		{
			filename = argv[nextArg];
			nextArg++;
		}
	}
	//End of processing command line arguments

	//if(filename != NULL)
	if(filename)
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
	int lineCapacity = 80;
	int lineSize = 0;

	//Start of real code
	//fgetc version
	int stop = 0;
	while(!stop)
	{
		char *storage = (char *)malloc(80 * sizeof(char));
		int capacity = 80;
		int size = 0;

		while(1)
		{
			int nextLetterRetval = fgetc(input);
			unsigned char nextLetter = (unsigned char)nextLetterRetval;

			//fprintf(stderr, "Received %d %d %d %d\n", (int)nextLetter, size, capacity, EOF);

			if(nextLetterRetval == EOF)
			{
				fprintf(stderr, "Got an EOF, uhoh! :(\n");
				stop = 1;
				break;
				//End of input or error case
			}
			if(nextLetter == '\n')
			{
				break;
			}
			if((size + 1) == capacity)
			{
				//reassign storage
				char *temp = (char *)malloc(capacity * 2 * sizeof(char));
				for(int i=0; i<size; i++)
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
		storage[size] = '\0';

		//fprintf(stdout, "User entered '%s'\n", storage);
		//fprintf(stdout, "Length Real %d, Length Ours %d\n", strlen(storage), length(storage));
		if(strlen(storage) != length(storage))
		{
			fprintf(stderr, "Lengths do not match: '%s'\n", storage);
		}

		if(lineSize == lineCapacity)
		{
			char **temp = (char **)malloc(lineCapacity * 2 * sizeof(char *));
			for(int i=0; i<lineSize; i++)
			{
				temp[i] = lines[i];
			}
			lineCapacity *= 2;
			free(lines);
			lines = temp;
		}

		lines[lineSize] = storage;
		lineSize++;
		//free(storage);
		//storage = NULL;
	}

	for(int i=0; i<lineSize; i++)
	{
		fprintf(stdout, "User entered '%s'\n", lines[i]);
	}

	//Getline version
	while(1)
	{
		int retval = getline(&buffer, &size, input);

		if(retval == -1)
		{
			int error = errno;
			fprintf(stderr, "Getline Error(%d): %s\n", error, strerror(error));
			break;
		}

		if(retval > 0)
		{
			int location = retval - 1;
			//location = strlen(buffer);

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
		buffer = NULL;
	}

	free(buffer);
	buffer = NULL;

	return 0;
}



size_t length(char *word)
{
	size_t retval = 0;

	int location = 0;
	while(*(word + location) != '\0')
	//while(word[location] != '\0')
	{
		retval++;
		location++;
	}

	return retval;
}

int compare(char *first, char *second)
{
	size_t sizeFirst = length(first);
	size_t sizeSecond = length(second);

	size_t loopMax = sizeFirst;
	if(sizeSecond < loopMax)
	{
		loopMax = sizeSecond;
	}

	for(size_t i=0; i<loopMax; i++)
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


