
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

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Error improper command line argument\n");
		return 1;
	}
	FILE *fp;
	int fd;
	fp = fopen(argv[1], "rb");
	fd = fileno(fp);
	if(fp == NULL)
	{
		fprintf(stderr, "Error opening file \n");
		return 2;
	}
	unsigned short casenum;
	//char buf[20];
	if(read(fd, &casenum, 2) == 0)
	{
		fprintf(stderr, "Error reading from file1\n");
		return 1;
	}
	//casenum = atoi(buf);
	struct ExecutionPair* thepair;
	//unsigned char tempmodel;
	//unsigned int tempsizeA, tempsizeB;
	char* tempcommand1;
	char* tempcommand2;
	unsigned int tempsizeA;
	unsigned int tempsizeB;
	unsigned char tempmodel;
	casenum = casenum /2;
	struct ExecutionPair* list[casenum];
	//create execution pair for later joseph
	for(int i = 0; i < casenum; i++)
	{
		//printf("c is %hu\n", casenum);
		thepair = (struct ExecutionPair*)malloc(sizeof(struct ExecutionPair));
		//printf("malloced for the pair\n");
		if(fread(&tempmodel, 1, 1, fp) == 0)
		{
			fprintf(stderr, "Error reading from file2 %d\n", feof(fp));
        	return 1;
		}
		//printf("buf is %s\n", buf);
		//tempmodel = atoi(buf);
		thepair->model = tempmodel;
		if(fread(&tempsizeA, 4, 1, fp) == 0)
		{
		 	fprintf(stderr, "Error reading from file3\n");
        	return 1;
		}
		//printf("buf is %s\n", buf);
		//tempsizeA = atoi(buf);
		thepair->sizeA = tempsizeA;
		if(fread(&tempsizeB, 4, 1, fp) == 0)
		{
			fprintf(stderr, "Error reading from file4\n");
        	return 1;
		}
		//printf("buf is %s\n", buf);
		//tempsizeB = atoi(buf);
		thepair->sizeB = tempsizeB;
		tempcommand1 = (char*)malloc(tempsizeA + sizeof(char));
		//printf("malloced tempcommand1\n");
		tempcommand2 = (char*)malloc(tempsizeB + sizeof(char));
		//printf("malloced tempcommand2\n");
		//printf("ta is %d, and tb is %d\n", tempsizeA, tempsizeB);
		if(fread(tempcommand1, tempsizeA, 1, fp) == 0)
		{
		 	fprintf(stderr, "Error reading from file5\n");
        	return 1;
		}
		strcat(tempcommand1, "\0");
		//changed from w/o & to &
		//address of string
		thepair->command1 = createCommand(tempcommand1, tempsizeA);
		//printf("%s\n", thepair->command1->argv[0]);
		//printf("pa->c1 is %s \n", thepair->command1);
		if(fread(tempcommand2, tempsizeB, 1, fp) == 0)
		{
			fprintf(stderr, "Error reading from file6\n");
        	return 1;
		}
		strcat(tempcommand2, "\0");
		thepair->command2 = createCommand(tempcommand2, tempsizeB);
		//printf("pa->c2 is %s \n", thepair->command2);
		list[i] = thepair;
		//printf("list[%d] malloc\n", i);
		execute(thepair);
	}
	int status;
	int val;
	//waitpid(-1, &status, 0);
	while(errno != ECHILD)
	{
		val = waitpid(-1, &status, 0);
		if(val == -1)
		{
			if(errno == ECHILD)
			{
				for(int j = 0; j < casenum; j++)
				{
					//printf("freed list[%d]\n", j);
					destroyExecPair(list[j]);
					//free(thepair);
				}
				fclose(fp);
				//free(thepair);
				return 0;
			}
			fprintf(stderr, "Wait returned an error (%d): %s\n", errno, strerror(errno));
		}
		if(WIFEXITED(status))
		{
			int returnValue = WEXITSTATUS(status);
			fprintf(stdout, "Child %d returned %d.\n", val, returnValue);
		}
		else
		{
			if(WIFSIGNALED(status))
			{
				int signalNum = WTERMSIG(status);
				fprintf(stdout, "Child %d terminated abnormally with signal %d\n", val, signalNum);
			}
			else
			{
				fprintf(stdout, "Child %d terminated abnormally.\n", val);
			}
		}
		if(errno && errno != ECHILD)
		{
			fprintf(stderr, "Exec failed (%d): %s\n", errno, strerror(errno));
			exit(5);
		}
	}
	fclose(fp);
	return 0;
}
