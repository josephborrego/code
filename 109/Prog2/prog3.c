#include<stdio.h>
#include<string.h>
#include<time.h>
#include"List.h"

int main(int argc, char **argv)
{
	struct Node *myList = constructList(0);

	if(argc != 3)
	{
		fprintf(stderr, "Not enough arguments: %s <count> <seed>\n", argv[0]);
		return 1;
	}
	int count = atoi(argv[1]);
	int seed = atoi(argv[2]);

	srand(seed);

	char commands[6] = "csifr";
	int errors = 0;
	int errorsT1 = 0;
	int errorsT2 = 0;
	for(int i=0; i<count; i++)
	{
		char rCommand = commands[rand() % 5];
		int rOption = rand() % 64;

		char command = ' ';
		char rBuffer[100];
		sprintf(rBuffer, "-%c:%d", rCommand, rOption);
		int option = 0;
		fprintf(stderr, "Processing command '%s'.\n", rBuffer);
		sscanf(rBuffer, "-%c:%d", &command, &option);
		switch(command)
		{
		case 'c':
			myList = destroyList(myList);
			myList = constructList(option);
			break;
		case 's':
			if(size(myList) != sizeAns(myListAns))
			{
				fprintf(stderr, "Mismatched size, wanted %ld got %ld.\n", sizeAns(myListAns), size(myList));
				errors++;
			}
			break;
		case 'i':
			myList = insert(myList, option);
			myListAns = insertAns(myListAns, option);
			break;
		case 'f':
			if(find(myList, option) != findAns(myListAns, option))
			{
				fprintf(stderr, "find(%d) does not match wanted %d, got %d.\n", option, findAns(myListAns,option), find(myList,option));
				errors++;
			}
			break;
		case 'r':
			myList = removeItem(myList, option);
			myListAns = removeItemAns(myListAns, option);
			break;
		}

		char *buffer = (char *)calloc(1, 250000 * sizeof(char));
		char *bufferAns = (char *)calloc(1, 250000 * sizeof(char));
		traverse(myList, buffer);
		traverseAns(myListAns, bufferAns);
		if(strcmp((const char *)buffer, (const char *)bufferAns) != 0)
		{
			fprintf(stderr, "Traversal does not match wanted %s, got %s\n", bufferAns, buffer);
			errorsT1++;
		}
		free(buffer);
		free(bufferAns);

		char *printable = traverse2(myList);
		char *printableAns = traverse2Ans(myListAns);

		if(printableAns == NULL)
		{
			if(printable != NULL)
			{
				if(printable[0] != '\0')
				{
					fprintf(stderr, "Secondary traversal does not match wanted '', did not get that.\n");
				}
			}
		}
		else if(strcmp(printable, printableAns) != 0)
		{
			fprintf(stderr, "Secondary traversal does not match wanted %s, got %s\n", printableAns, printable);
			errorsT2++;
		}
		free(printable);
		free(printableAns);
	}

	myList = destroyList(myList);
	myListAns = destroyListAns(myListAns);
	//valgrind should report no memory leaks at this point

	fprintf(stdout, "Error count: Normal %d, Traverse %d, Traverse2 %d\n", errors, errorsT1, errorsT2);

	return 0;
}
