#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include"Command.h"
#include"ExecutionPair.h"

void destroyExecPair(struct ExecutionPair* pp)
{
		destroyCommand(pp->command1);
		destroyCommand(pp->command2);
		free(pp);
}

int execute(struct ExecutionPair* pair)
{
	pid_t childIDa;
	childIDa = fork();
	if(childIDa == -1)
	{
		fprintf(stderr, "Fork failed (%d) :%s\n", errno, strerror(errno));
		return 1;
	}
	if(childIDa != 0)
	{
		//parent
		return childIDa;
	}
	pid_t childIDb;
	//connects the two together
	int fd[2];
	//pipe is created
	int retval = pipe(&fd[0]);
	if(retval == -1)
	{
		fprintf(stderr, "Pipe failed: (%d): %s\n", errno, strerror(errno));
		exit(1);
	}
	//output of the program
	int resultfd[2];
	retval = pipe(&resultfd[0]);
	if(retval == -1)
    {
        fprintf(stderr, "Pipe failed: (%d): %s\n", errno, strerror(errno));
        exit(1);
    }
	childIDb = fork();
	if(childIDb == -1)
    {
     	fprintf(stderr, "Fork failed (%d) :%s\n", errno, strerror(errno));
        exit(1);
    }

	unsigned char twoout = pair->model >>6;
	unsigned char twoin = pair->model >>4;
	unsigned char oneout = pair->model >>2;
	unsigned char onein = pair->model;

	unsigned char temponein = onein &3;
	unsigned char temponeout = oneout &3;
	unsigned char toneout = oneout & 3;
	unsigned char temp2in = twoin & 3;
	unsigned char temp2out = twoout & 3;

	if(childIDb == 0)
	{
		//1in
		temponein = onein &3;
		if(temponein == 3)
		{
			temponeout = oneout &3;
			//1out
			if(temponeout == 2)
			{
				fprintf(stderr, "Error wrong 2-bit value1 (%d) :%s\n", errno, strerror(errno));
				exit(1);
			}
			//difficulty here
			//we're getting input from the pipe, so we're closing the output side of the pipe
			close(fd[1]);
			close(resultfd[0]);
			close(STDIN_FILENO); //closing standard in of this thread
			dup(fd[0]);
			close(fd[0]);
			close(STDOUT_FILENO);
			dup(resultfd[1]);
			close(resultfd[1]);
		}
		else
		{
			toneout = oneout & 3;
			if((toneout) == 1)
            {
				/* Later joseph's problem*/
            }
			else
			{
				close(fd[0]);
            	close(resultfd[1]);
            	close(STDOUT_FILENO); //closing standard out of this thread
            	dup(fd[1]);
            	close(fd[1]);
            	close(STDIN_FILENO);
            	dup(resultfd[0]);
            	close(resultfd[0]);
			}
		}
		int retval = execvp(pair->command1->argv[0], pair->command1->argv);
		if(retval == -1)
		{
			fprintf(stderr, "Exec failed (%d): %s\n", errno, strerror(errno));
			destroyCommand(pair->command1);
			exit(3);
		}
		//execution pair related
	}
	else
	{
		temp2in = twoin & 3;
		if((temp2in) != 1)
		{
			temp2out = twoout & 3;
			if((temp2out) == 0)
			{
				//not logical output going to command1 and coming from command1
            close(fd[1]);
            close(resultfd[0]);
            close(STDIN_FILENO); //closing standard in of this thread
            dup(fd[0]);
            close(fd[0]);
            close(STDOUT_FILENO);
            dup(resultfd[1]);
            close(resultfd[1]);
			}
		}
		else
		{
		}
		int retval = execvp(pair->command2->argv[0], pair->command2->argv);
        if(retval == -1)
        {
            fprintf(stderr, "Exec failed (%d): %s\n", errno, strerror(errno));
			destroyCommand(pair->command2);
            exit(3);
        }
	}
exit(1);
}
