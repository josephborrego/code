#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<cerrno>
#include<cstring>
#include<fctnl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std;

int main(int argc, char **argv)
{
	int mySocket;
	mySocket = socket(AF_INET, SOCK_STREAM, 0);

	if(mySocket == -1)
	{
		cerr << "Socket Failed: (" << errno << ") " << strerror(errno) << endl;
		return 1;
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
		linger linger_option = {1, 10}; // how long do we consider the connection dead or not
		setsockopt(mySocket, SOL_SOCKET, SO_LINGER, &linger_option, sizeof(linger));

		if(option == -1)
		{
			cerr << "Couldn't set longer option" << endl;
			return 3;
		}

		if(listen(mySocket, 10) == -1)
		{
			if(errno == EADDRINUSE)
			{
				port++;
				continue;
			}
			cerr << "Failed listen(" << errno << "); " << strerror(errno) << endl;
			return 4;
		}
		retry = false;
	}
	cerr << "Got port number :" << port << endl;
	while(1)
	{
		sockaddr_in otherAddr;
		memset(&otherAddr, 0, sizeof(sockaddr_in));
		socklen_t, otherLen;
		memset(&otherLen, 0, sizeof(socklen_t));
		otherLen = sizeof(sockaddr_in);
		int otherSocket = accept(mySocket, (sockaddr*)&ptherAddr, &otherLen);
		if(otherSocket == -1)
		{
			cerr << "Accept failed (" << errno << "): " << strerror(errno) << endl;
			continue;
		}
		int ip = ntohl(otherAddr.sin_addr.s_addr);
		int top = (ip >> 24) & 0xff;
		int sec = (ip >> 16) &0xff;
		int thi = (ip >> 8) & 0xff;
		int foh = ip & 0xff;
		int otherPort = ntohs(otherAddr.sin_port);
		cout << "Accepted a connection from: "
		cout <<  top << "." << sec << "." << thi << "." <<  foh;
		cout << " on port: " << otherPort << endl;
		char letter;
		while(read(otherSocket, &letter, 1) == 1)
		{
			cerr << "Read value: " << letter << endl;
		}
		cerr <<"Exited read loop" << endl
	}
	return 0;
}
