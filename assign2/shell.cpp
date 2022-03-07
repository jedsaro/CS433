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

int main()
{

  vector<char*> data_storage;

  char *args[MAX_LINE / 2 + 1]; // holds arguments
  char str[MAX_LINE];           // holds user input

  int should_run = 1;
  char *token;

  char gr = *">";
  char lr = *"<";
  char hs = *"!!";

  pid_t pid;

  while (should_run)
  {

    printf("SH> ");
    fflush(stdout);

    fgets(str, sizeof(str), stdin);

    int x = 0;
    args[x] = strtok(str, " \n");
    while (args[x] != NULL)
    {
      // printf("%s\n", args[x]);
      x++;
      args[x] = strtok(NULL, " \n");


      //data_storage.push_back(args[x]);

    }

    cout << data_storage.front();


    pid_t pid = fork();

    if (pid < 0)
    {
      fprintf(stderr, "Fork Failed");
      exit(0);
    }

    if (pid == 0)
    {

      if (*args[0] == hs)
      {
        cout << "temp";
      }

      cout << "child: " << pid << endl;
      
      execvp(args[0], &args[0]);

      /*
      else if (true)
      {
        cout << "working!!!!!!!!!!!!!!!!! '>'  \n";
      }
      

      else if (*args[1] == lr)
      {
        cout << "working!!!!!!!!!!!!!!!!! '>' \n";
      }
      */

      
    }

    wait(NULL);

    cout << "parent: " << pid << endl;
  }
}