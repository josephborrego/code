#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<cerrno>
#include<cstring>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/wait.h>

using namespace std;

int processBuffer(char *buffer, int size)
{
	int retval = 0;
	if(!buffer)
	{
		return retval;
	}

	for(int i=0; i<size; i++)
	{
		if((buffer[i] == '\r') || (buffer[i] == '\n'))
		{
			retval++;
			for(int j=i+1; j<size; j++)
			{
				buffer[j-1] = buffer[j];
			}
			size--;
			i--;
		}
	}

	return retval;
}

//int retval[];

void handler(int num)
{
    write(STDOUT_FILENO, "Received signal\n",16);
	int status;
	while(waitpid(-1, &status, WNOHANG|WUNTRACED) > 0)
	{
		//Check errors, possibly handle return values
		//retval[id] = ...
	}

}

int main(int argc, char **argv)
{
	int mySocket;
	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mySocket == -1)
	{
		cerr << "Socket failed: (" << errno << ") " << strerror(errno) << endl;
		return 1;
	}

    sighandler_t signalRetval = signal(SIGCHLD, &handler);
    if(signalRetval == SIG_ERR)
    {
        fprintf(stderr, "Signal failed: (%d): %s\n", errno, strerror(errno));
    }


	sockaddr_in serve;
	memset(&serve, 0, sizeof(sockaddr_in));
	serve.sin_family = AF_INET;
	serve.sin_addr.s_addr = htonl(INADDR_ANY);

	short port = 10000;
	bool retry = true;
	while(retry)
	{
		if(port > 15000)
		{
			cerr << "Could not acquire a port, aborting" << endl;
			return 2;
		}
		serve.sin_port = htons(port);
		int bound = bind(mySocket, (sockaddr *)&serve, sizeof(sockaddr_in));
		if(bound == -1)
		{
			port++;
			continue;
		}

		linger linger_option = {1, 10};
		int option = setsockopt(mySocket, SOL_SOCKET, SO_LINGER, &linger_option, sizeof(linger));
		if(option == -1)
		{
			cerr << "Couldn't set linger option" << endl;
			return 3;
		}

		if(listen(mySocket, 10) == -1)
		{
			if(errno == EADDRINUSE)
			{
				port++;
				continue;
			}
			cerr << "Failed listen (" << errno << "): " << strerror(errno) << endl;
			return 4;
		}
		retry = false;
	}

	cerr << "Got port number: " << port << endl;

	while(1)
	{
		sockaddr_in otherAddr;
		memset(&otherAddr, 0, sizeof(sockaddr_in));
		socklen_t otherLen;
		memset(&otherLen, 0, sizeof(socklen_t));
		otherLen = sizeof(sockaddr_in);

		int otherSocket = accept(mySocket, (sockaddr*)&otherAddr, &otherLen);
		if(otherSocket == -1)
		{
			cerr << "Accept failed (" << errno << "): " << strerror(errno) << endl;
			continue;
		}

		int ip = ntohl(otherAddr.sin_addr.s_addr);
//		cerr << "Original ip data: " << otherAddr.sin_addr.s_addr << endl;
//		cerr << "Raw ip data: " << ip << endl;
		int first = (ip >> 24) & 0xff;
		int second = (ip >> 16) & 0xff;
		int third = (ip >> 8) & 0xff;
		int fourth = ip & 0xff;
		int otherPort = ntohs(otherAddr.sin_port);
		cout << "Accepted a connection from: ";
		cout << first << "." << second << "." << third << "." << fourth;
		cout << " on port: " << otherPort << endl;

		pid_t childID = fork();
		if(childID == -1)
		{
			cerr << "Failed to fork: " << errno << ": " << strerror(errno) << endl;
		}
		if(childID == 0)
		{
			char letter;
			int value = 0;
			while(read(otherSocket, &letter, 1) == 1)
			{
				if((letter == '\r') || (letter == '\n'))
				{
					continue;
				}

				bool ok = false;
				if((letter == ' ') || isdigit(letter))
				{
					ok = true;
				}

				if(!ok)
				{
					continue;
				}

				if((letter == '0') && (value == 0))
				{
					break;
				}
				else
				{
					if(letter == ' ')
					{
						//We have the value. And we can start reading the data.
						cerr << "Received value: " << value << endl;
						char *buffer = (char *)malloc((value * sizeof(char))+11);
						int howMuchWeRead = 0;
						int location = 0;
						int left = value;
						while(left > 0)
						{
							int howMuchWeRead = read(otherSocket, &buffer[location], left);
							if(howMuchWeRead == -1)
							{
								cerr << "Error in reading: " << errno << ": " << strerror(errno) << endl;
								break;
							}
							else if(howMuchWeRead == 0)
							{
								cerr << "Connection terminated abruptly" << endl;
								break;
							}
							int removed = processBuffer(buffer, location+howMuchWeRead);

							howMuchWeRead -= removed;

							location += howMuchWeRead;
							left -= howMuchWeRead;
						}
						int result = 0;
						for(int i=0; i<value; i++)
						{
							result += (int)buffer[i];
						}

						sprintf(buffer, "%d", result);

						int howMuchWeWrote = 0;
						location = 0;
						left = strlen(buffer);
						while(left > 0)
						{
							int howMuchWeWrote = write(otherSocket, &buffer[location], left);
							if(howMuchWeWrote == -1)
							{
								cerr << "Error in writing" << endl;
								break;
							}
							else if(howMuchWeWrote == 0)
							{
								cerr << "Connection broken" << endl;
								break;
							}
							location += howMuchWeWrote;
							left -= howMuchWeWrote;
						}
						free(buffer);
						value = 0;
					}
					else
					{
						value *= 10;
						value += letter - '0';
					}
				}
				//cerr << "Read value: '" << letter << "' (" << (unsigned short)letter << ")" << endl;
				//write(otherSocket, &letter, 1);
			}
			return 0;
		}

		cerr << "Child has been spawned off" << endl;
		//int status;
		//int waitVal = wait(&status);
		//checks

		//cerr << "Exited read loop / Child has died." << endl;

	}

	return 0;
}
