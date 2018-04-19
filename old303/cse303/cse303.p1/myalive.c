#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <getopt.h>
#include "support.h"

//flags
volatile int alarmf = 0;
volatile int controlf = 0;
//handlers
void alarmh()
{
    alarmf = 1;
}
void controlh()
{
    controlf = 1;
}
//alive function
void alive()
{
    struct timeval now;
    //timeval, timezone
    gettimeofday(&now, NULL);
    time_t staht = now.tv_sec;
    //sig number, function pointer
    signal(SIGALRM, alarmh);
    signal(SIGINT, controlh);
    //10 second wait
    size_t true = 1;
    alarm(10);
        while(true)
        {
            //alarmf = 1
            if(alarmf)
            {
                struct timeval check;
                gettimeofday(&check, NULL);
                time_t dun = check.tv_sec;
                time_t tyme = dun - staht;
                fprintf(stdout, "Time took: %d seconds\n", (int)tyme);
                exit(1);
            }
            //controlf = 1
            if(controlf)
            {
                fprintf(stdout, "\n no \n");
                controlf = 0;
            }
        }
}
//helper function
void helper(char* pro)
{
    fprintf(stdout, "Used %s \n", pro);
    fprintf(stdout, "SIGINT = ctrl + c, SIGAlRM = alarm clock \n");
}
//main
int main(int argc, char** argv)
{
    long op;
    //name check
    check_student(argv[0]);
    //parse com lin
    while((op = getopt(argc, argv,"h")) != -1)
    {
        switch(op)
        {
            case 'h':helper(argv[0]);
            break;
        }
    }
    alive();
}

