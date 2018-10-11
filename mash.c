#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXIN 255
#define MAXCMDS 4
#define MAXARGS 5
#define PRESEP "­­­­­-----CMD "
#define SEP "--------------------------------------------------------------------------------"

int main(int argc, char const *argv[])
{
  //String Array and memory allocation
  char *userCommands[MAXCMDS];
  for (int i = 0; i < MAXCMDS; i++)
  {
    userCommands[i] = malloc(MAXIN);
  }

  //Command 1
  printf("Welcome to MASH!\nmash-1>");
  fgets(userCommands[0], MAXIN, stdin);
  printf("Full: %s\n", userCommands[0]);
  char *cmd1[MAXARGS];
  char *cmd1_token = strtok(userCommands[0], " ");

  for (int i = 0; i < MAXARGS; i++)
  {
    if (cmd1_token != NULL)
    {
      cmd1[i] = cmd1_token;
      printf("cmd1[%d]=%s\n", i, cmd1[i]);
      cmd1_token = strtok(NULL, " ");
    }
    else
    {
      cmd1[i] = NULL;
    }
  }
  printf("cmd1 size: %d\n", sizeof(cmd1));

  //Command 2
  printf("mash-2>");
  fscanf(stdin, "%s", userCommands[1]);

  //Command 3
  printf("mash-3>");
  fscanf(stdin, "%s", userCommands[2]);

  //File path
  printf("file>");
  fscanf(stdin, "%s", userCommands[3]);

  return 0;
}
