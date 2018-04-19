
/*
CSE 109: Spring 2017
<Joseph Borrego>
<job218>
<Server>
Program #7
*/
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <fcntl.h>
#include <sys/mman.h>

void sigchld_handler(int num)
{
  //printf("in sig handler\n");
  while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char **argv)
{
	//if the argument counter does not equal 2 print error message
	if(argc != 2)
	{
		fprintf(stderr, "Incorrect usage: ./Server <filename>\n");
		return 1;
	}
	//create a file pointer
	FILE *fp;
	//open binary read 
	fp = fopen(argv[1], "rb");
	//file pointer check
	if(fp == NULL)
	{
		return '\0';
	}
	int mySocket;
	signal(SIGCHLD, sigchld_handler);
	/* create the socket*/
	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mySocket == -1)
	{
		fprintf(stderr, "Socket Failed: (%d) %s\n", errno, strerror(errno));
		return 1;
	}
	char sendbuff[250];
	struct sockaddr_in serve;
	memset(&serve, 0, sizeof(struct sockaddr_in));
	memset(sendbuff, 0, sizeof(sendbuff));
	/*AF_INET is internetwork */
	serve.sin_family = AF_INET;
	serve.sin_addr.s_addr = htonl(INADDR_ANY);
	//serve.sin_port = 0;
	int retry = 1;
	short port = 10000;
	short endport = 10500;

	while(retry)
	{
		if(port > endport)
		{
			fprintf(stderr, "Could not acquire a port, aborting\n");
			return 2;
		}
		serve.sin_port = htons(port);
		int bound = bind(mySocket, (struct sockaddr *)&serve, sizeof(struct sockaddr_in));
		if(bound == -1)
		{
			//printf("yo\n");
			port++;
			continue;
		}
		struct linger lin = {0};
		lin.l_onoff = 1;
		lin.l_linger =  10;
		int option = setsockopt(mySocket, SOL_SOCKET, SO_LINGER, (const char*) &lin, sizeof(lin));
		if(option == -1)
		{
			fprintf(stderr,"Couldn't set linger option\n");
			return 3;
		}
		if(listen(mySocket, 10) == -1)
		{
			if(errno == EADDRINUSE)
			{
				//printf("ay\n");
				port++;
				continue;
			}
			fprintf(stderr, "Failed listen (%d): %s \n", errno, strerror(errno));
			return 4;
		}
		retry = 0;
	}
	FILE *connectfp;
	connectfp = fopen("connection.txt", "wb");
	if(fwrite(&port, 2, 1, connectfp) == 0)
	{
		return -1;
	}
	char host[100];
	gethostname(host, sizeof(host));
	int a = strlen(host);
	if(fwrite(&a, 4, 1, connectfp) == 0)
	{
		return -1;
	}
	if(fwrite(&host, a, 1, connectfp) == 0)
	{
		return -1;
	}
	int b = strlen(argv[1]);
	if(fwrite(&b, 4, 1, connectfp) == 0)
	{
		return -1;
	}
	if(fwrite(argv[1], b, 1, connectfp) == 0)
	{
		return -1;
	}
	fclose(connectfp);
	int* running = (int*)malloc(sizeof(int));
	int shm_fd;
    int* shared_memory;
	int msize; // the size (in bytes) of the shared memory segment 
    const char *name = "RUNNING";
	shm_unlink(name);
	// calculating the array size based on the number of terms being passed from child to parent
    msize = sizeof(int);
    shm_fd = shm_open (name, O_CREAT | O_EXCL | O_RDWR, S_IRWXU | S_IRWXG);
    if (shm_fd < 0)
    {
        fprintf(stderr,"Error in shm_open()");
        return -3;
    }
	ftruncate(shm_fd, msize);
	shared_memory = (int *) mmap(NULL, msize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == NULL) 
    {
        fprintf(stderr,"Error in mmap()");
        return -3;
    }
	shared_memory[0] = 1;
	*running = 1;
	int confd = 0;
	struct sockaddr_in otheraddr;
	memset(&otheraddr, 0, sizeof(otheraddr));
	int c = sizeof(struct sockaddr_in);
	int start;
	int amount;
	unsigned short datasize;
	//int deez;
	struct timeval tv;
	tv.tv_sec = (long) 2;
    tv.tv_usec = 0;
	//struct SOCKET
	fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(mySocket, &rfds);
	//while(*running == 1)
	while(shared_memory[0] == 1)
	{
		memset(&otheraddr, 0, sizeof(struct sockaddr_in));
		int a = fcntl(mySocket, F_SETFL, O_NONBLOCK);
		if(a == -1)
		{
			//printf("error\n");
		}
		confd = accept(mySocket, (struct sockaddr*)&otheraddr, (socklen_t*)&c);
		fflush(stdout);
		if(confd == 0)
		{
			//printf("zero\n");
		}
		if(confd == -1)
		{
			if(*running == 0)
			{
			return -1;
			}
			continue;
		}
		else
		{
			//printf("cunnect\n");
		}
		pid_t childID = fork();
		//printf("forking\n");
		if(childID == -1)
		{
			fprintf(stderr, "Failed to fork: %d: %s \n", errno, strerror(errno));
			return -1;
		}
		if(childID == 0)
		{
			if(recv(confd, &datasize, 2, 0) == -1)
			{
				return -1;
			}
			if(recv(confd, &start, 4, 0) == -1)
			{
				return -1;
			}
			if(recv(confd, &amount, 4, 0) == -1)
        	{
            	return -1;
        	}
			if(amount == 0)
			{
				if(start == 0)
				{
					shared_memory[0] = 0;
					*running = 0;
				}
			}
			void *data = (void*)malloc(amount);
			unsigned char total;
			unsigned char temp;
			//integrity check
			for(int i = 0; i < (datasize - 10); i+= 2)
			{
				if(recv(confd, &temp, 2, 0) == -1)
				{
					return -1;
				}
				total += temp;
			}
			//printf("b4 fseek1\n");
			if(fseek(fp, start, SEEK_SET) != 0)
			{
				return -1;
			}
			//printf("b4 fseek2\n");
			if(amount > 0)
			{
				if(fread(data, amount, 1, fp) == 0)
				{
					if(!feof(fp))
					{
						return -1;
					}
					//continue;
				}
			}
			int sentdata;
			//printf("b4 feof\n");
			if(feof(fp))
			{
				sentdata = ftell(fp);
				sentdata =  sentdata - start;
			}
			else
			{
				sentdata = amount;
			}
			//printf("b4 write1\n");
			if(write(confd, &sentdata, 4) <= 0)
			{
				return -1;
			}
			//printf("b4 write2\n");
			if(write(confd, &total, 1) <= 0)
			{
				return -1;
			}
			//printf("b4 write3\n");
			if(write(confd, data, sentdata) <= 0)
			{
				return -1;
			}
			//printf("freeing data\n");
			free(data);
			return 0;
		}
	}
	fclose(fp);
	//fclose(connectfp);
	return 0;
}
