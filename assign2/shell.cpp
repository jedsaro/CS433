/**
 * After reading user input, the steps are:
 * (1) fork a child process using fork()
 * (2) the child process will invoke execvp()
 * (3) parent will invoke wait() unless command included &
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

#define MAX_LINE 80 /* The maximum length command */

// TODO: create a .h file and clean code into functions if possible

void executeChild(char *array)
{
  // Forking a child
  pid_t pid = fork();

  if (pid == 0)
  {
    if (execvp(&array[0], &array) < 0)
    {
      printf("\nCould not execute command..");
    }
    exit(0);
  }
  else if (pid == -1)
  {
    printf("\nFork Failed");
    return;
  }
  else
  {
    wait(NULL);
    return;
  }
}


bool input(char* array){

  cin.getline(array, MAX_LINE);

  if (sizeof(*array) != 1){

    //!(@briana) add history here
    //ex.. history(array);

    return false;
  }

  cout << "NO COMMANDS" << endl;

  return true;
}


int main(void)
{

  // char *args[MAX_LINE / 2 + 1]; /* command line arguments */


  //* user input--------------------------

  char userInput[MAX_LINE]; 

  //char *args[MAX_LINE/2 + 1] ;


  int should_run = 1; /* flag to determine when to exit program */

  while (should_run)
  {

    printf("osh-> ");
    fflush(stdout);

    if(input(userInput)){
      continue;
    }

    executeChild(userInput);

    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included &
     */

    break;
  }

  return 0;

}
