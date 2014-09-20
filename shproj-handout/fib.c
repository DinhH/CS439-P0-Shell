#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

const int MAX = 13;

static void doFib(int n, int doPrint);


/*
 * unix_error - unix-style error routine.
 */
inline static void 
unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}


int main(int argc, char **argv)
{
  int arg;
  int print;

  if(argc != 2){
    fprintf(stderr, "Usage: fib <num>\n");
    exit(-1);
  }

  if(argc >= 3){
    print = 1;
  }

  arg = atoi(argv[1]);
  if(arg < 0 || arg > MAX){
    fprintf(stderr, "number must be between 0 and %d\n", MAX);
    exit(-1);
  }

  doFib(arg, 1);

  return 0;
}

/* 
 * Recursively compute the specified number. If print is
 * true, print it. Otherwise, provide it to my parent process.
 *
 * NOTE: The solution must be recursive and it must fork
 * a new child for each call. Each process should call
 * doFib() exactly once.
 */
//Kahli is driving
static void doFib(int n, int doPrint)
{
	pid_t child1;
	pid_t child2;
	int status1;
	int status2;
	int val1;
	int val2;

	if (n == 0 || n == 1) {
		if (doPrint == 1){
			printf( "%d\n", n);
			exit(n);
		}
		else{
			exit(n);
		}
	} 	

	child1 = fork();

	if (child1 == 0){
		doFib(n-1, 0);//doesn't return;
	}
//End of Kahli driving, Dinh driving now
	else {
		waitpid(child1,&status1,0);	
		val1 = WEXITSTATUS(status1);	
		child2 = fork();
		if (child2 == 0){
			doFib(n-2, 0);
		}
		else {
			waitpid(child2, &status2,0);
			val2 = WEXITSTATUS(status2);
			if (doPrint == 1) {
				printf("%d\n", (val1 + val2));
			}
			else {
				exit(val1 + val2);
			}
		}
	}
}
//End of Dinh driving.


