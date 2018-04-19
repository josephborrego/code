#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "support.h"
#include "Client.h"

void help(char *progname)
{
	printf("Usage: %s [OPTIONS]\n", progname);
	printf("Perform a PUT or a GET from a network file server\n");
	printf("  -P    PUT file indicated by parameter\n");
	printf("  -G    GET file indicated by parameter\n");
	printf("  -s    server info (IP or hostname)\n");
	printf("  -p    port on which to contact server\n");
	printf("  -S    for GETs, name to use when saving file locally\n");
}

void die(const char *msg1, const char *msg2)
{
	fprintf(stderr, "%s, %s\n", msg1, msg2);
	exit(0);
}

/*
 * connect_to_server() - open a connection to the server specified by the
 *                       parameters
 */
int connect_to_server(char *server, int port)
{
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;
	char errbuf[256];                                   /* for errors */

	/* create a socket */
	if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		die("Error creating socket: ", strerror(errno));
	}

	/* Fill in the server's IP address and port */
	if((hp = gethostbyname(server)) == NULL)
	{
		sprintf(errbuf, "%d", h_errno);
		die("DNS error: DNS error ", errbuf);
	}
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)hp->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
	serveraddr.sin_port = htons(port);

	/* connect */
	if(connect(clientfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
	{
		die("Error connecting: ", strerror(errno));
	}
	return clientfd;
}

/*
 * echo_client() - this is dummy code to show how to read and write on a
 *                 socket when there can be short counts.  The code
 *                 implements an "echo" client.
 */
void echo_client(int fd)
{
	// main loop
	while(1)
	{
		/* set up a buffer, clear it, and read keyboard input */
		const int MAXLINE = 8192;
		char buf[MAXLINE];
		bzero(buf, MAXLINE);
		if(fgets(buf, MAXLINE, stdin) == NULL)
		{
			if(ferror(stdin))
			{
				die("fgets error", strerror(errno));
			}
			break;
		}

		/* send keystrokes to the server, handling short counts */
		size_t n = strlen(buf);
		size_t nremain = n;
		ssize_t nsofar;
		char *bufp = buf;
		while(nremain > 0)
		{
			if((nsofar = write(fd, bufp, nremain)) <= 0)
			{
				if(errno != EINTR)
				{
					fprintf(stderr, "Write error: %s\n", strerror(errno));
					exit(0);
				}
				nsofar = 0;
			}
			nremain -= nsofar;
			bufp += nsofar;
		}

		/* read input back from socket (again, handle short counts)*/
		bzero(buf, MAXLINE);
		bufp = buf;
		nremain = MAXLINE;
		while(1)
		{
			if((nsofar = read(fd, bufp, nremain)) < 0)
			{
				if(errno != EINTR)
				{
					die("read error: ", strerror(errno));
				}
				continue;
			}
			/* in echo, server should never EOF */
			if(nsofar == 0)
			{
				die("Server error: ", "received EOF");
			}
			bufp += nsofar;
			nremain -= nsofar;
			if(*(bufp-1) == '\n')
			{
				*bufp = 0;
				break;
			}
		}

		/* output the result */
		printf("%s", buf);
	}
}

/*
 * put_file() - send a file to the server accessible via the given socket fd
 */
void put_file(int fd, char* put_name)
{
  /* TODO: implement a proper solution, instead of calling the echo() client */
  while(1)
    {
      bool checksum = false;
      char buf[1024];
      bzero(buf, 1024);
      if(fgets(buf, 1024, stdin))
	{
	  if(strstr(buf, "PUT"))
	    {
	      char* pfilename = put_name;
	      for(; *pfilename != '\n'; ++pfilename)
		{
		  if(isprint(*pfilename) < 0)
		    {
		      fprintf(stderr, "Invalid filename \"%c\"\n", *pfilename);
		      continue;
		    }
		}
	      pfilename = put_name;
	      if(write(fd, buf, strlen(buf) - 1) < 0)
		{
		  printf("error writing \n");
		  exit(0);
		}
	      if(strstr(buf, "PUTC"))
		{
		  checksum = true;
		}
	      char sizebuf[1024];
	      bzero(sizebuf, 1024);
	      if(fgets(sizebuf, 1024, stdin))
		{
		  for(char* pdigit = sizebuf; *pdigit != '\n'; ++pdigit)
		    {
		      if(!isdigit(*pdigit))
			{
			  fprintf(stderr, "Size must be in decimal\n");
			  break;
			}
		    }
		}

	      if(write(fd, sizebuf, strlen(sizebuf)-1) < 0)
		{
		  printf(" error writing in pdigit \n");
		  exit(0);
		}

	      char data[1024];
	      bzero(data, 1024);
	      if(fgets(data, 1024, stdin))
		{
		  for(char* pdata = data; *pdata != '\n'; ++pdata)
		    {
		      if(!isprint(*pdata))
			{
			  printf("error data has to be printable\n");
			  break;
			}
		    }
		}
		//task 3
		if(checksum)
		{
		unsigned char result[MD5_DIGEST_LENGTH];
		bzero(result, sizeof(result));
		MD5(reinterpret_cast<unsigned char*>(data), strlen(data) + 1, result);
		//printf("writing MD5 hash %s\n", result);
		write(fd, result, strlen(reinterpret_cast<char*>(result)) + 1);
		}
	      if(write(fd, data, strlen(data)-1) < 0)
		{
		  printf("write failed\n");
		  exit(0);
		}
	    }
	  else
	    {
	      fprintf(stdout, "Usage: PUT [filename]\n");
	      continue;
	    }
	}

      else
	{
	  fprintf(stderr, "fgets failed %s\n", strerror(errno));
	  exit(0);
	}
    }//end while
}


void readinput(const int fd, char* buffer, int bytesread)
{
  while(1)
    {
      const int MAXLINE = 8192;
      char      buf[MAXLINE];   /* a place to store text from the client */
      bzero(buf, MAXLINE);
      /* read from socket, recognizing that we may get short counts */
      char *bufp = buf;              /* current pointer into buffer */
      ssize_t nremain = MAXLINE;     /* max characters we can still read */
      size_t nsofar;                 /* characters read so far */
      while (1)
    {
      /* read some data; swallow EINTRs */
      if((nsofar = read(fd, bufp, nremain)) < 0)
        {
          if(errno != EINTR)
        {
          die("read error: ", strerror(errno));
        }
          continue;
        }
      /* end service to this client on EOF */
      if(nsofar == 0)
        {
          fprintf(stderr, "received EOF\n");
          exit(0);
        }
      /* update pointer for next bit of reading */
      bufp += nsofar;
      nremain -= nsofar;
      //printf("current string \"%s\"\n", bufp-nsofar);
      strcpy(buffer, bufp - nsofar);
      return;
    }
    }
}


/*
 * get_file() - get a file from the server accessible via the given socket
 *              fd, and save it according to the save_name
 */
void get_file(int fd, char* get_name, char* save_name)
{
	while(1)
	{
		char buff[1024];
		bzero(buff, 1024);
		if(fgets(buff, 1024, stdin))
		{
			const char* getfile = buff;
			//getfile+= 4;
			if(strstr(buff, "GET"))
			{
				for(; *getfile != '\n'; ++getfile)
				{
					//printf("|%c|\n",*getfile);
					if(!isprint(*getfile) && !isspace(*getfile))
					{
						fprintf(stderr, "Invalid filename %s\n", getfile);
						return;
					}
				}
				write(fd, buff, strlen(buff) - 1);
				//write(fd, save_name, strlen(save_name));
				FILE* fp = fopen(save_name, "a+");
				if(!fp)
				{
					printf("Error could not open file\n");
					continue;
				}
				char data[1024];
				readinput(fd, data, 0);
				fputs(data, fp);
				fclose(fp);
			}
			else
			{
				fprintf(stdout, "Usage: GET [filename]\n");
				continue;
			}
		}
		else
		{
			fprintf(stdout, "fgets failed\n");
			exit(0);
		}
	} //end of while
}

/*
 * main() - parse command line, open a socket, transfer a file
 */
int main(int argc, char **argv)
{
	/* for getopt */
	long  opt;
	char *server = NULL;
	char *put_name = NULL;
	char *get_name = NULL;
	int   port;
	char *save_name = NULL;

	check_team(argv[0]);

	/* parse the command-line options. */
	while((opt = getopt(argc, argv, "hs:P:G:S:p:")) != -1)
	{
		switch(opt)
		{
		case 'h': help(argv[0]); break;
		case 's': server = optarg; break;
		case 'P': put_name = optarg; break;
		case 'G': get_name = optarg; break;
		case 'S': save_name = optarg; break;
		case 'p': port = atoi(optarg); break;
		}
	}

	/* open a connection to the server */
	int fd = connect_to_server(server, port);

	/* put or get, as appropriate */
	if(put_name)
	{
		put_file(fd, put_name);
	}
	else
	{
		get_file(fd, get_name, save_name);
	}

	/* close the socket */
	int rc;
	if((rc = close(fd)) < 0)
	{
		die("Close error: ", strerror(errno));
	}
	exit(0);
}
