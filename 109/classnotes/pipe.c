#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char **argv)
{
	int pipefd(2);
	int retval = pipe(&pipefd[0]);

	if(retval == -1)
	{
		fprintf(stderr, "Pipe failed: (%d): %s\n", errno, strerror(errno));
		return 2;
	}
	int resultfd[2];
	pid_t childID = fork();
	if(childID == -1)
	{
		fprintf(stderr, "Fork failed: (%d): %s\n", errno, strerror(errno));
		return 1;
	}
	printf("about to wait, childID: %d\n", childID);
//	sleep(1);
	if(childID == 0)
	{
		//Child
		close(pipefd[1]);
		close(resultfd[0]);
		close(STDIN_FILENO);
		dup(pipefd[0]);
		close(pipefd[0]);
		close(STDOUT_FILENO);
		dup(resultfd[1]);
		close(resultfd[1]);
		unsigned char *space = (unsigned char*)malloc(40);
		unsigned char *excess = (unsigned char*)malloc(4);
		int carryover = 0;
		while(1)
		{
			if(carryover)
			{
				memcpy(space, excess, carryover);
			}
			int howMuch = read(pipefd[0], space + carryover, 40 - carryover);
			printf(stderr, "Read returned: %d\n", howMuch);
			if(howMuch == -1)
			{
				fprintf(stderr, "Read failed (%d): %s\n", errno, strerror(errno));
			}
			if(howMuch == 0)
			{
				printf("recieved EOF\n");
				break;
			}
			howmuch+= carryover;
			int howMany = howMuch / 4;
			for(int i = 0; i < howMany; i++)
			{
				int number = *(((int*)space) + i);
				printf("Recieved %d.\n", number);
			}
			int printed = howMany + 4;
			int leftover = howMuch - printed;
			if(leftover > 0)
			{
				fprintf(stderr, "There are %d leftover, unprinted, bytes.\n", leftover);
				memcpy(excess, space + printed, leftover);
				carryover = leftover;
			}
			else
			{
				carryover = 0;
			}
		}
		close(pipefd[0]);
		free(space);
		return 0;
	}
	else
	{
		//Parent
		close(pipefd[0]);
		srand(0);
		for(int i = 0; i < 2; i++)
		{
			int howManyToSend = 16;
			int toMalloc = (howManyToSend * sizeof(int)) + 2;
			unsigned char *space = (unsigned char*)malloc(howManyToSend * sizeof(int));
			for(int i = 0; i < 16; i++)
			{
				int value = rand() % 256;
				int *location = ((int*)space) + i;
				*location = value;
//			(((int*)space) + i) = value;
//			write(pipefd[1], &value, 4);
			}
			space[toMalloc - 2] = 'A';
			space[toMalloc - 1] = 'B';
			write(pipefd[1], space, howManyToSend * sizeof(int));
			sleep(4);
			free(space);
		}
		close(pipefd[1]);
	}
	int status = 0;
	int waitValue = wait(&status);
	printf("Wait returned %d.\n", waitValue);
	return 0;
}
