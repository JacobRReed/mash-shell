#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXIN 255
#define MAXCMDS 4
#define MAXARGS 4
#define PRESEP "­­­­­-----CMD "
#define SEP "--------------------------------------------------------------------------------"

struct Command
{
  char *base;
  char **arguments; //array of pointers
  int count;
};

//Takes a commands string and splits by spaces, returning a string array, including command
struct Command splitCommand(char *cmd)
{
  char *cmdArgs[MAXARGS];

  char *cmd_token = strtok(cmd, " "); //set pointer to first space
  cmd_token = strtok(NULL, " ");      //Chop off first command
  char *cmdFirst = strtok(cmd, " ");  //First command
  int totalArgs = 0;                  //argument counter
  struct Command retCommand;          //command struct
  retCommand.base = cmdFirst;

  //Loop through and get all args
  for (int i = 0; i < MAXARGS; i++)
  {
    if (cmd_token != NULL)
    {
      totalArgs++;
      cmdArgs[i] = cmd_token;
      cmd_token = strtok(NULL, " ");
    }
  }

  retCommand.arguments = cmdArgs;
  retCommand.count = totalArgs;
  return retCommand;
}

//MAIN
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
  struct Command cmd1 = splitCommand(userCommands[0]);
  printf("%s ", cmd1.base);
  printf("%s ", cmd1.arguments[0]);
  printf("%s ", cmd1.arguments[1]);
  return 0;
}
