#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char **argv)
{
<<<<<<< HEAD
	pid_t process1;
	kill(getpid(),SIGUSR1);
=======
	int arg;
	arg = atoi(argv[1]);
	kill(arg,SIGUSR1);	
>>>>>>> cb50140586805ea50f5960b228717f9835dcd1e8
  return 0;
}
