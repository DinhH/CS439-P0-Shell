
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "util.h"

/*
 * First, print out the process ID of this process.
 *
 * Then, set up the signal handler so that ^C causes
 * the program to print "Nice try.\n" and continue looping.
 *
 * Finally, loop forever, printing "Still here\n" once every
 * second.
 */

void INThandler(int);

int main(int argc, char **argv)
{
	pid_t process1;
	printf("%d\n",getpid()); // --> FIXED PID PRINTING TWICE
   	Signal(SIGINT,INThandler);
   	
   	int run = 1; 
	struct timespec* time1= (struct timespec*)malloc(sizeof(struct timespec));
	time1->tv_nsec = 10000000;
      	int x;

	while(run==1){
		for (x=0; x <100; x++) { 
		nanosleep(time1,0);
		}
		write(1, "Still Here.\n", 12); 
	}   
	return 0;
}
void INThandler(int sig)
{
   write(1, "Nice try.\n", 10);
}
