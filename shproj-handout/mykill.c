#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

//Kahli is driving
int main(int argc, char **argv)
{
	int arg;
	arg = atoi(argv[1]);
	kill(arg,SIGUSR1);	
  return 0;
}
//end of Kahli driving.
