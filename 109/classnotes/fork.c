
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

void handler(int num)
{
	write(STDOUT_FILENO, "Recieved signal\n", 16);

}

int anyChildLeft(pid_t *array, int size)
{
	for(int i = 0; i <size; i++)
	{
		if(array[i] != 0)
		{
			return 1;
		}
	}
	return 0;
}

int clearChild(pid_t *array, int size, pid_t toClear)
{

}
//creates a new proces by duplicating the calling process
int main(int argc, char **argv)
{
	int value = 5;
	pid_t childArray[10];
	pid_t childID;

	for(int i = 0; i < 10; i++)
	{
		 childID = fork()

		if(childID == -1)
		{
			fprintf(stderr, "Fork failed (%d): %s\n", errno, strerror(errno));
			return 1;
		}
		if(childID == 0)
		{
			break;
		}

		childArray[i] = childID;
}
	char *firstArg = argv[1];

	if(childID == 0)
	{
		char **argv = (char**)malloc(4 * sizeof(char*));
		argv[0] = (char*)malloc(10 * sizeof(char));
		argv[1] = (char*)malloc(10 * sizeof(char))
		argv[2] = (char*)malloc(10 * sizeof(char));
		argv[3] = NULL;

		if(argc > 1)
		{
			strcpy(argv[0], firstArg);
		}
		else
		{
		strcpy(argv[0], "./p1");
		}

		strcpy(argv[1], "banana");
		strcpy(argv[2], "carrot");
		int retval = execvp(argv[0], argv);
		fprintf(stderr, "Exec failed(%d): %s\n", errno, strerror(errno));

		free(argv[0]);
		free(argv[1]);
		free(argv[2]);
		free(argv);

		return 1;
	}

	printf("Return value from fork: %d", childID);
	printf("We have the value 5: %d\n", value);
	value++;
	printf("We have the value 6: %d\n", value);
	printf("about to wait for our child\n");
	int status = 0;

	for(anyChildLeft(childArray, 10)
	{
		int waitValue = wait(&status);
		clearChild(childArray, 10, waitValue);
		if(waitValue == -1)
		{
			fprintf(stderr, "Wait returned an error (%d): %s\n", errno, strerror(errno));
		}

		printf("our child has died, recieved %d\n", waitValue);
		if(WIFEXITED(status)
		{
			int returnValue = WEXITSTATUS(status);
			printf("our child has returned %d\n", status);
		}
		else
		{
			printf("Child terminated abnormally\n");
			if(WIFSIGNALED(status))
			{
				int signalnum = WTERMSIG(status);
				printf("Killed by signal %d.\n", signalnum);
			}
		}
		for(int j = 0; j < 10; j++)
		{
			printf("%d", childArray[i];
		}
	}
	return 0;
}
