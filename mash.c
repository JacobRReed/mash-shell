#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXIN 255
#define MAXARGS 5 //or support infinite for extra credit

int main(int argc, char const *argv[])
{
  //String Array and memory allocation
  char *userCommands[MAXARGS];
  for (int i = 0; i < MAXARGS; i++)
  {
    userCommands[i] = malloc(MAXIN);
  }

  //Command 1
  printf("Welcome to MASH!\nmash-1>");
  fscanf(stdin, "%s", userCommands[0]);

  //Command 2
  printf("mash-2>");
  fscanf(stdin, "%s", userCommands[1]);

  //Command 3
  printf("mash-3>");
  fscanf(stdin, "%s", userCommands[2]);

  //File path
  printf("file>");
  fscanf(stdin, "%s", userCommands[3]);

  //TEST OUT
  printf("Size of userCommands: %d\n", userCommands);
  printf("Size of each command: %lu\n", sizeof(&userCommands[0]));
  printf("Command #1: %s\nCommand #2: %s\nCommand #3: %s\nFile Command: %s", userCommands[0], userCommands[1], userCommands[2], userCommands[3]);

  return 0;
}
