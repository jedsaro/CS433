#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
<<<<<<< HEAD
#include <vector>
#include <fcntl.h>
=======
#include <fcntl.h>
#include <vector>
#include <errno.h>
>>>>>>> josef

using namespace std;

#define MAX_LINE 80
<<<<<<< HEAD

void history_command()
{
  cout << "im working mommy\n";
}

vector<char> add_history(char **args)
{

  vector<char> data(**args, 2);

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

  if (*args[1] == gr)
  {
    cout << "working!!!!!!!!!!!!!!!!! '>'  \n";
  }

  if (*args[1] == lr)
  {
    cout << "working!!!!!!!!!!!!!!!!! '>' \n";
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

  // add_history(args);
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
=======

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
void checkRedirect(char **args);

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

    checkRedirect(args);

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
>>>>>>> josef

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

<<<<<<< HEAD
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
=======
void checkRedirect(char **args)
{
  int redirect;
  int fd;

  for (int i = 0; args[i] != NULL; i++)
  {
    if (strcmp(args[i], "<") == 0)
    {
      fd = open(args[i + 1], O_RDONLY);
      dup2(fd, STDIN_FILENO);
      args[i], args[i + 1] = NULL;
      redirect = 1;
    }
    else if (strcmp(args[i], ">") == 0)
    {
      fd = open(args[i + 1], O_WRONLY | O_CREAT, 0644);
      dup2(fd, STDOUT_FILENO);
      args[i], args[i + 1] = NULL;
      redirect = 2;
    }
    else
    {
      continue;
    }
  }
}
>>>>>>> josef
