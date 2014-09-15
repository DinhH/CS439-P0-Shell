
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "util.h"

//**********BIG PROBLEM IS THAT WE CAN'T DO KILL********
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
	pid_t child;
	printf("%d\n",getpid()); // --> FIXED PID PRINTING TWICE
   	Signal(SIGINT,INThandler);
   	
   	int run = 1; //if kill hasn't been called
	//the way we created the struct was wrong. So I tried the struct to a pointer
	struct timespec* time1= (struct timespec*)malloc(sizeof(struct timespec));
	//and I think we only need the nano second.
	time1->tv_nsec = 10000000;
      	int x;

	while(run==1){
		//I used the for loop to multifly out to 1 second. (10000000*100 = 1 second)
		for (x=0; x <100; x++) {//I am not sure if the for loop is the best 
		//we don't need the "&" anymore because it's a pointer now
		nanosleep(time1,0);
		}
		write(1, "Still Here.\n", 12); 
	}   
	return 0;
}
//ISSUES: ^C prints when running; sometimes nanosecond
//num value is less than zero and prints "woops";
void INThandler(int sig)
{
   write(1, "Nice try.\n", 10);
}
