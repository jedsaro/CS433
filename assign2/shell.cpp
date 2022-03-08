#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <vector>

using namespace std;

#define MAX_LINE 80

vector<string> data;

char input[MAX_LINE / 2 + 1];
char *args[MAX_LINE];
char token;
int should_run = 1;

char gr = *">";
char lr = *"<";
char hs = *"!!";

void user_input();
void commands();
void shell();

int main()
{

  // start the shell
  shell();

  return 0;
}

void shell()
{
  while (should_run)
  {
    // get the command from user
    user_input();

    // fit the command into *argv[]
    commands();

    /*   if (data.empty())
      {
        for (int i; i < 5; i++)
          data.insert(data.begin() + i, argv[i]);
      }
   */
    //! kill me please
    if (*args[0] == hs)
    {
      cout << data.back();
    }
    /*    for (int i = 0; i < 5; i++)
       {
         cout << argv[i] << endl;
       }
    */
    // fork and execute the command
    pid_t pid = fork();

    if (pid < 0)
    {
      fprintf(stderr, "Fork Failed");
      exit(0);
    }

    if (pid == 0)
    {

      // execute a command
      execvp(args[0], args);
    }
    else
    {
      // wait for the command to finish if "&" is not present
      if (NULL == args[token])
        waitpid(pid, NULL, 0);

      /*  if (!data.empty())
       {
         data.clear();
         for (int i; i < 5; i++)
           data.insert(data.begin() + i, argv[i]);
       } */
    }
  }
}

void user_input()
{
  // get command from user
  printf("Shell>\t");
  fgets(input, MAX_LINE / 2 + 1, stdin);

  if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
    input[strlen(input) - 1] = '\0';
    
  // printf("%s\n", cmd);
}

void commands()
{

  // split string into argv
  char *ptr;
  token = 0;
  ptr = strtok(input, " ");
  while (ptr != NULL)
  {
    args[token] = ptr;
    token++;
    ptr = strtok(NULL, " ");
  }
}
