	#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<getopt.h>

    //we're expanding the size of the pointer old_nums to a new pointer which we call new_n$
    //expand the array that tracks the free space in the chunks
    int *expand(int *old_nums, int new_size)
    {
        int* new_nums = (int *)malloc(new_size * sizeof(int));
        for(size_t j = 0; j< new_size - 1; j++)
        {
            new_nums[j] = old_nums[j];
        }
        free(old_nums);
        return new_nums;
    }

    //expand function for bucket
    char **expandbuck(char **old_bucket, int new_size)
    {
     	//create a new chunk (row of characters)
        char **newbucket = (char **)malloc(new_size * sizeof(char*));
        for(size_t k = 0; k< new_size - 1; k++)
        {
            newbucket[k] = old_bucket[k];
        }
        free(old_bucket);
        return newbucket;
    }

    //insert word in the pointer line
    //then we see add the location and the strlen of the word
    char *insertword(char *line, char *word, int location)
    {
        for(size_t g = 0; g < strlen(word); g++)
        {
            line[location + g] = word[g];
//			printf("character is %c\nlocation is %d\n", word[g], (location+g));
        }
        line[(location + strlen(word))] = '\0';
        return line;
    }

  //main method
  int main(int argc, char *argv[])
    {
        //get the argv
        size_t chunksize = 100;
        if(argc == 2)
        {
            chunksize = atoi(argv[1]);
        }
        if(argc > 2)
        {
            fprintf(stderr, "Invalid Option\n");
            exit(EXIT_FAILURE);
        }
        //check if its between 20 and 100000 inclusive
        if(chunksize < 5 || chunksize > 100000)   //MAKE SURE TO CHANGE BEFORE SUBMITTING
        {
            fprintf(stderr, "Invalid option\n");
            exit(EXIT_FAILURE);
        }
        //array of all chunks
        char **bucket = (char **)malloc(100 * sizeof(char*));
        //read in word
        char *typedline = (char *)malloc((chunksize ) * (sizeof(char)) );
        //how much free space is in the chunk
        int *chunkspace = (int *)malloc(sizeof(int));
        // how much chunkspace is allowed
        chunkspace[0] = chunksize;
        // we start with numchunks equal to 1 then dynamically allocate
        // memory to adjust
        // number of chunks in the bucket
        size_t numchunks = 1;
		size_t temp;
        size_t location;
        size_t foundspace = 0;
        //initialize the bucket
        bucket[0] = (char *)malloc(sizeof(char) * chunksize);
//		printf("chunksize is %d\n", chunksize);
        //while(fgets(typedline, chunksize , stdin) != NULL)
		while(fscanf(stdin,"%s", typedline) != EOF)
        {
            temp  = strlen(typedline);
		//	printf("start temp %d\n", temp);
            foundspace = 0;
            for(size_t p = 0 ; p < numchunks ; p++)
            {
		//		printf("chunkspace is %d >= temp is %d\n", chunkspace[p], temp);
                if(chunkspace[p] >= temp + 1)
                {
		//			printf("inside the if\n");
                    location = chunksize - chunkspace[p];
                    //this was a problem
                    bucket[p] = insertword(bucket[p], typedline, location);
					//we need to manually account for the null character
                    chunkspace[p] = chunkspace[p] - (strlen(typedline)) - 1; //**changed
		//			printf("chunkspace is now %d\n", chunkspace[p]);
                    foundspace = 1;
                    break;
                }
            }

  				// make a new chunk method after you go through all your chunks
                //print out the chunks
                if(!foundspace)
                {
                    //dynamically creating new chunks
                    bucket = expandbuck(bucket, numchunks + 1);
                    bucket[numchunks] = (char *)malloc (sizeof(char) * chunksize);
                    chunkspace = expand(chunkspace, numchunks + 1);
                    chunkspace[numchunks] = chunksize;
					location = chunksize - chunkspace[numchunks];
                    //this was a problem
                    bucket[numchunks] = insertword(bucket[numchunks], typedline, location);
					//we need to manually account for the null character
                    chunkspace[numchunks] = chunkspace[numchunks] - (strlen(typedline)) -1 ; //**changed
                    foundspace = 1;
                    //counter for numchunks
                    numchunks++;
                }
            }


    //size_t temp;
    size_t width;
    for(size_t i = 0; i < numchunks; i++)
    {
        temp = chunksize - chunkspace[i];
		if( temp < 10) { width = 1; }
		else if( temp < 100) { width = 2; }
		else if( temp < 1000) { width = 3; }
		else if( temp < 10000) { width = 4; }
		else if( temp < 100000) { width = 5; }
		else { temp = 6; }
        for(size_t q = 0; q < (6 - width); q++)
        {
            printf(" ");
        }
        printf("%d: ", temp);
        for(size_t j = 0; j < temp; j++)
        {
        // use double equals when comparing
        // use single equals for assigning
            if(bucket[i][j] == '\0')
            {
                printf(" ");
            }
			else if (bucket[i][j] == '\n')
			{
				printf(" ");
			}
        //if it's a null print a space, but if it's anything then just print the letter ins$
            else
            {
                printf("%c", bucket[i][j]);
            }
    }
        printf("\n");
}
	free(typedline);
	free(chunkspace);
	for(int i = 0; i < numchunks; i++)
	{
		free(bucket[i]);
	}
	free(bucket);
    return 0;
}

