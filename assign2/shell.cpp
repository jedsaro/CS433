#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <fcntl.h>

using namespace std;

#define MAX_LINE 80

void history_command()
{
  cout << "im working mommy\n";
  

}

vector<char> add_history(char ** args)
{

  vector<char> data (**args,2);

  return data;

}

//*listens for special commands specified by the assignment

char commands_hub(char **args)
{

  char gr = *">";
  char lr = *"<";
  char history = *"!!";

  if (*args[0] == history)
  {
    history_command();
  }

  //! unable to make it work

  /*   if (*args[1] == gr || *args[1] == lr)
    {
      if (*args[1] == gr)
      {
        int fds = open(args[2], O_WRONLY);
        dup2(fds, 1);
        // execvp(args[0], &args[2]);
        close(0);
      }
    } */
}

bool takeInput(char *str, char **args)
{
  fgets(str, sizeof(str), stdin);

  int x = 0;
  args[x] = strtok(str, " \n");
  while (args[x] != NULL)
  {
    // printf("%s\n", args[x]);
    x++;
    args[x] = strtok(NULL, " \n");
  }

  add_history(args);
  commands_hub(args);

  if (sizeof(args[0] != NULL))
  {
    return true;
  }

  return false;
}

int main()
{

  char *args[MAX_LINE / 2 + 1]; // holds arguments
  char str[MAX_LINE];           // holds user input

  int should_run = 1;
  char *token;

  pid_t pid;

  while (should_run)
  {

    printf("SH> ");
    fflush(stdout);

    takeInput(str, args);

    pid = fork();

    if (pid < 0)
    {
      fprintf(stderr, "Fork Failed");
      return 1;
    }
    else if (pid == 0)
    {
      execvp(args[0], &args[0]);
    }
    else
    {
      wait(NULL);
    }
  }
}