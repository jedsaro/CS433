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

char input[MAX_LINE / 2 + 1];
char *args[MAX_LINE];
char token;
int should_run = 1;
bool breaker = false;

char gr = *">";
char lr = *"<";
char hs = *"!!";

char *history1;

void user_input();
void commands();
void shell();
bool checkRedirect(char **args);

int main()
{

  shell();

  return 0;
}

void shell()
{
  while (should_run)
  {
    user_input();

    commands();

    if (strcmp(args[0], "exit") == 0)
    {
      break;

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
        }

        if (breaker)
        {
          break;
        }
      }
    }
  }
}

void user_input()
{

  printf("osh> ");

  fgets(input, MAX_LINE / 2 + 1, stdin);

  if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
    input[strlen(input) - 1] = '\0';
}

void commands()
{

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
  }

  if (strcmp(args[0], "!!") == 0)
  {
    if (history1 == NULL)
    {
      cout << "No history found" << endl;
    }
    
    answer = false;
  }
  else
  {
    answer = true;
  }

  return answer;
}