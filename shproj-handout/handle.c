#include <assert.h>
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
   pid_t child;
   int status;
   int run = 1; //if kill hasn't been called

   child = fork();
   
	if(child!=0){
		 waitpid(child,&status,0); //EXPLAINATION BELOW  
	}
   printf("%d\n",getpid()); // --> FIXED PID PRINTING TWICE
   while(run!=0){
      struct timespec time1;
      int num;

      time1.tv_sec = 1;
      time1.tv_nsec = 0;
      num = nanosleep(&time1,NULL);
      if(num<0)
         printf("woops\n"); //filler
 
     //Still Here prints funky
     //EXPLAINATION: our code was printing funky because
     //the child and parent were executing the code at the 
     //same time. I fixed this with the conditional up top
     //so that only the child process executes and the parent waits. 
      else if(num==0){
	ssize_t bytes; 
	const int STDOUT = 1; 
	bytes = write(STDOUT, "Still here.\n", 10); 
	printf("\n");
	if(bytes != 10) 
	   exit(-999);
      }
      
      signal(SIGINT,INThandler);
     
     /* //If user hits crtl-c
      
      {
         ssize_t bytes; 
         const int STDOUT = 1; 
         bytes = write(STDOUT, "Nice try.\n", 10); 
         if(bytes != 10) 
         exit(-999);
      }*/
   }   
  return 0;
}
//ISSUES: ^C prints when running; sometimes nanosecond
//num value is less than zero and prints "woops";
void INThandler(int sig)
{
   signal(sig,SIG_IGN);
   ssize_t bytes; 
   const int STDOUT = 1; 
   bytes = write(STDOUT, "Nice try.\n", 10); //This only print once 
   if(bytes != 10) 
      exit(-999);
   signal(SIGINT,INThandler);
}
