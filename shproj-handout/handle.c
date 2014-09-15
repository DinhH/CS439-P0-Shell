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
int main(int argc, char **argv)
{
   int child;
   int run = 1; //if kill hasn't been called

   //GetPID prints 2 nums
   child = fork();
   printf("%d\n",getpid());

	
   while(run!=0)
   {
      struct timespec time1,time2;
      int num;

      time1.tv_sec = 1;
      time2.tv_sec = 0;
      num = nanosleep(&time1,&time2);
      if(num<0)
         printf("woops\n");
 
     //Still Here prints funky
     else if(num==0)
      {
	ssize_t bytes; 
	const int STDOUT = 1; 
	bytes = write(STDOUT, "Still here.\n", 10); 
	printf("\n");
	if(bytes != 10) 
	   exit(-999);
      }
      
      /*
      else
      {
         ssize_t bytes; 
         const int STDOUT = 1; 
         bytes = write(STDOUT, "Nice try.\n", 10); 
         if(bytes != 10) 
         exit(-999);
      }
      sleep(1);*/
   }   
   
  return 0;
}


