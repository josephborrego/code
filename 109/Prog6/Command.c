#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include"Command.h"

struct Command* createCommand(char* string, int size)
{
//	printf("in command, string is %s\n", string);
	struct Command* comm = (struct Command*)malloc(sizeof(struct Command));
	//printf("malloc for comm\n");
	comm->comstring = (char*)malloc(size + sizeof(char));
	//printf("malloced for comm->comstring\n");
	comm->size = size;
	strcpy(comm->comstring, string);
	char* string2 = (char*)malloc(size + sizeof(char));
	//printf("malloc for string2\n");
	strcpy(string2, string);
	char* token;
    const char q[2] = " ";
    token = strtok(string, q);
    int count = 0;
    while( token != NULL)
    {
    	count++;
        token = strtok(NULL, q);
    }
	//printf("count is %d\n", count);
	comm->argc = count;
	comm->argv = (char**)malloc((count + 1) * sizeof(char*));
	//printf("malloc for com->argv\n");
    for(int i = 0; i < count; i++)
    {
    	comm->argv[i] = (char*)malloc(10000 * sizeof(char));
		//printf("malloc for comm->argv[i]\n");
    }
	comm->argv[count] = NULL;
    //we now have room for all the command line arguments, now we need to copy into what we malloced
    int c = 0;
	//printf("com->comstring is %s\n", comm->comstring);
    token = strtok(string2, q);
    while(token != NULL)
    {
        strcpy(comm->argv[c],token);
	//	printf("com->argv[c] is %s\n", comm->argv[c]);
        token = strtok(NULL, q);
	//	printf("token is %s\n", token);
        c++;
    }
	//printf("freeing string2\n");
	free(string2);
	//printf("freeing string\n");
	free(string);
	return comm;
}

struct Command* destroyCommand(struct Command* com)
{
	//command, argv, string
	for(int i = 0; i < com->argc ; i++)
	{
		//printf("freeing com->argv[i]\n");
		free(com->argv[i]);
	}
	//printf("free com->argv\n");
	free(com->argv);
	//printf("free com->comstring\n");
	free(com->comstring);
	//printf("free com\n");
	free(com);
	return NULL;
}
