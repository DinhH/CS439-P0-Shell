/* 
 * msh - A mini shell program with job control * 
 * <Put your name and login ID here>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "util.h"
#include "jobs.h"


/* Global variables */
int verbose = 0;            /* if true, print additional output */

extern char **environ;      /* defined in libc */
static char prompt[] = "msh> ";    /* command line prompt (DO NOT CHANGE) */
static struct job_t jobs[MAXJOBS]; /* The job list */
/* End global variables */


/* Function prototypes */

/* Here are the functions that you will implement */
void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

/* Here are helper routines that we've provided for you */
void usage(void);
void sigquit_handler(int sig);



/*
 * main - The shell's main routine 
 */
int main(int argc, char **argv) 
{
    char c;
    char cmdline[MAXLINE];
    int emit_prompt = 1; /* emit prompt (default) */

    /* Redirect stderr to stdout (so that driver will get all output
     * on the pipe connected to stdout) */
    dup2(1, 2);

    /* Parse the command line */
    while ((c = getopt(argc, argv, "hvp")) != EOF) {
        switch (c) {
        case 'h':             /* print help message */
            usage();
	    break;
        case 'v':             /* emit additional diagnostic info */
            verbose = 1;
	    break;
        case 'p':             /* don't print a prompt */
            emit_prompt = 0;  /* handy for automatic testing */
	    break;
	default:
            usage();
	}
    }

    /* Install the signal handlers */

    /* These are the ones you will need to implement */
    Signal(SIGINT,  sigint_handler);   /* ctrl-c */
    Signal(SIGTSTP, sigtstp_handler);  /* ctrl-z */
    Signal(SIGCHLD, sigchld_handler);  /* Terminated or stopped child */

    /* This one provides a clean way to kill the shell */
    Signal(SIGQUIT, sigquit_handler); 

    /* Initialize the job list */
    initjobs(jobs);

    /* Execute the shell's read/eval loop */
    while (1) {

	/* Read command line */
	if (emit_prompt) {
	    printf("%s", prompt);
	    fflush(stdout);
	}
	if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
	    app_error("fgets error");
	if (feof(stdin)) { /* End of file (ctrl-d) */
	    fflush(stdout);
	    exit(0);
	}

	/* Evaluate the command line */
	eval(cmdline);
	fflush(stdout);
	fflush(stdout);
    } 

    exit(0); /* control never reaches here */
}  
  
/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
*/
int bg;
void eval(char *cmdline) 
{
    	char *arg[MAXLINE];
	pid_t child,pgid;
	int status;
	sigset_t *set, *oldset;

	//Signal(SIGINT,sigint_handler);
	bg = parseline(cmdline,arg);
	if(arg[0]==NULL)
	{
<<<<<<< HEAD
		if(arg[0]==NULL){
			return;
		}
		else{ 
			execv(arg[0],arg);
		}
	}
	/*else if(bg==0)
	{
		//wait for running command to terminate
	}*/
=======
		return;
	}
	
>>>>>>> 680d946d9631724a1b153a1832d41c52826e917e
	if(builtin_cmd(arg)==1)
	{
		int val = execv(arg[0],arg);
		return;	
		//exit(val);
	}
	
	else
	{
		sigprocmask(SIG_BLOCK,set,oldset);
		child=fork();
		if(child==0)
		{
			pgid = setpgid(child,pgid);
			sigprocmask(SIG_UNBLOCK,set,oldset);
			int val = execv(arg[0],arg);
			if(bg==0) // if foreground
				waitfg(pgid);
		}
		else//parent
			addjob(jobs,pgid,bg,cmdline);
			sigprocmask(SIG_UNBLOCK,set,oldset);
		return;
	}
}

/* 
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.  
 * Return 1 if a builtin command was executed; return 0
 * if the argument passed in is *not* a builtin command.
 */
int builtin_cmd(char **argv) 
{
	if(strcmp(argv[0],"quit")==0)
		exit(1);
	else if(argv[0]=="fg"||argv[0]=="bg"||bg==1)
		do_bgfg(argv);
	else if(strcmp(argv[0],"jobs")==0)
		return(1);
	else{
	//printf("this is a non-build-in : %s\n",argv[0]);
	return 0;}     /* not a builtin command */
}

/* 
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv) 
{	
/*	if(argv[1]==0)
	{
<<<<<<< HEAD
		if(argv[0]==NULL){
			return;
		}
		else{ 
			execv(argv[0],argv);
		}
	} 

	else
	{
		pid_t kid=fork();
		if(kid!=0)
		{
			waitfg(kid);
		}
		else
		{
			
		}
	}	

	return;
=======
		printf("Arguement for the Command Line is Missing");
	}
	else if(arg[0] is num)
	{
		struct job_t *p = getjobpid(jobs,arg[1]);
	}
	else if(arg[0] is a job id with % sign)
	{
		struct job_t *p = getjobjid(jobs,arg[1]);
	}	
	return; */
>>>>>>> 680d946d9631724a1b153a1832d41c52826e917e
}

/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid)
{
	struct job_t *p= getjobpid(jobs,pid);
	while(p->state==0)
	{
		sleep(0);
	} 	
    return;
}

/*****************
 * Signal handlers
 *****************/

/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  
 */
void sigchld_handler(int sig) 
{
	pid_child;
	int status;
	while ((pid = waitpid(-1,&status, WNOHANG | WUNTRACED)) > 0) {
		deletejob(jobs,child);
	}
    return;
}

/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
void sigint_handler(int sig) 
{
	//don't need to have condition check
	if(sig==SIGINT)
	{
		//send to foreground
	}
    return;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void sigtstp_handler(int sig) 
{
    return;
}

/*********************
 * End signal handlers
 *********************/



/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void) 
{
    printf("Usage: shell [-hvp]\n");
    printf("   -h   print this message\n");
    printf("   -v   print additional diagnostic information\n");
    printf("   -p   do not emit a command prompt\n");
    exit(1);
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig) 
{
    ssize_t bytes;
    const int STDOUT = 1;
    bytes = write(STDOUT, "Terminating after receipt of SIGQUIT signal\n", 45);
    if(bytes != 45)
       exit(-999);
    exit(1);
}



