#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <vector>
#include <errno.h>

using namespace std;

#define MAX_LINE 80

vector<char *> data;

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
bool checkRedirect(char **args);

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
          data.insert(data.begin() + i, args[i]);
      }
   */
    //! kill me please
    /*     if (*args[0] == hs)
        {
          cout << data.back();
        }
     */
    /*    for (int i = 0; i < 5; i++)
       {
         cout << argv[i] << endl;
       }
    */
    // fork and execute the command

    if (checkRedirect(args))
    {

      pid_t pid = fork();

      if (pid < 0)
      {
        fprintf(stderr, "Fork Failed");
        exit(0);
      }

      if (pid == 0)
      {
        // execute a command
        if (execvp(args[0], args))
        {
          perror("Command not found\n");
        };
      }
      else
      {

        wait(NULL);

        /*  if (!data.empty())
         {
           data.clear();
           for (int i; i < 5; i++)
             data.insert(data.begin() + i, argv[i]);
         } */
      }
    }
  }
}

void user_input()
{
  // get command from user
  printf("osh>");

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

bool checkRedirect(char **args)
{
  int redirect;
  int fd;
  bool answer;

  for (int i = 0; args[i] != NULL; i++)
  {
    if (strcmp(args[i], "<") == 0)
    {
      fd = open(args[i + 1], O_RDONLY);
      dup2(fd, STDIN_FILENO);
      args[i], args[i + 1] = NULL;
      redirect = 1;
      answer = false;
    }
    else if (strcmp(args[i], ">") == 0)
    {
      fd = open(args[i + 1], O_WRONLY | O_CREAT, 0644);
      dup2(fd, STDOUT_FILENO);
      args[i], args[i + 1] = NULL;
      redirect = 2;
      answer = false;
    }
    else{
      answer = true;
    }
  }
  return answer;
}