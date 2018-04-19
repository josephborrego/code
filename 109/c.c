#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
	//Bucket points to (char *) which are our chunks
	char **bucket = NULL;

	int numChunks = 0;
	int chunkCapacity = 10;

	//Keep track of the size of each chunk
	int *chunkSize = NULL;

	char *buffer = NULL;
	while(fscanf(stdin, "%ms", &buffer) == 1)
	{
		int wordSize = strlen(buffer) + 1;

		//Find appropriate bucket.
		int found = -1;
//		for(int i=0; (i<numChunks) && (found == -1); i++)
		for(int i=0; i<numChunks; i++)
		{
			char *chunk = bucket[i];
			int currentUsedSpace = chunkSize[i];
			int totalNeeded = currentUsedSpace + wordSize;
			if(totalNeeded < chunkCapacity)
			{
				found = i;
				break;
			}
		}

		//We don't have a chunk
		if(found == -1)
		{
			char **tempBucket = (char **)malloc((numChunks+1) * sizeof(char *));
			for(int i=0; i<numChunks; i++)
			{
				tempBucket[i] = bucket[i];
			}
			free(bucket);
			bucket = tempBucket;

			int *tempChunkSize = (int *)malloc((numChunks+1) * sizeof(int));
			for(int i=0; i<numChunks; i++)
			{
				tempChunkSize[i] = chunkSize[i];
			}
			free(chunkSize);
			chunkSize = tempChunkSize;

			chunkSize[numChunks] = 0;
			bucket[numChunks] = (char *)malloc(chunkCapacity * sizeof(char));

			found = numChunks;
			numChunks++;
		}

		//Insert word into bucket[found];
		int locationToInsert = chunkSize[found];
		char *toInsert = bucket[found];
		char *insertionPoint = toInsert + locationToInsert;
		strcpy(insertionPoint, buffer);

		//strcpy(&bucket[found][chunkSize[found]], buffer);

		chunkSize[found] += wordSize;

		free(buffer);
		buffer = NULL;
	}
	free(buffer);
	buffer = NULL;

	for(int i=0; i<numChunks; i++)
	{
		fprintf(stdout, "%6d: ", chunkSize[i]);
		for(int j=0; j<chunkSize[i]; j++)
		{
			char toPrint = bucket[i][j];
			if(bucket[i][j] == '\0')
			{
				toPrint = ' ';
			}
			fprintf(stdout, "%c", toPrint);
		}
		fprintf(stdout, "\n");
	}

	for(int i=0; i<numChunks; i++)
	{
		free(bucket[i]);
		bucket[i] = NULL;
	}
	free(bucket);
	bucket = NULL;
	free(chunkSize);
	chunkSize = NULL;


	return 0;
}
