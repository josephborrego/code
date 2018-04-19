
/*
CSE 109: Spring 2017
<Joseph Borrego>
<Job218>
<Client>
Program #7
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char **argv)
{

	FILE *fp;
    fp = fopen("connection.txt", "rb");
    if(fp == NULL)
    {
     	return NULL;
    }



	return 0;
}
