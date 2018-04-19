#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#ifndef OURSTRING_C
#define OURSTRING_C
#include"ourstring.h"


size_t length(char *word)
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

int compare(char *first, char *second)
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

#endif
