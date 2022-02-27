#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */

//TODO: get user input

int main(void)
{	
	char *args[MAX_LINE/2 + 1]; /* command line arguments */

  	int should_run = 1; /* flag to determine when to exit program */

	fork();

	printf("Tu mama\n");
	  
	while (should_run) {

		printf("osh> ");
		fflush(stdout);
		

		//execvp(, args)recive array 

		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) parent will invoke wait() unless command included &
		*/

		should_run = 0;
	}
	return 0;
}