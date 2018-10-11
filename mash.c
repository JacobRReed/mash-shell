#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXIN 255
#define MAXARGS 5 //or support infinite for extra credit

int main(int argc, char const *argv[])
{
  //String Array
  char *userCommands[MAXIN];

  //Command 1
  printf("Welcome to MASH!\nmash-1>");
  fscanf(stdin, "%s", userCommands[0]);

  //Command 2
  printf("\nmash-2>");
  fscanf(stdin, "%s", userCommands[1]);

  //Command 3
  printf("\nmash-3>");
  fscanf(stdin, "%s", userCommands[2]);

  //File path
  printf("\nfile>");
  fscanf(stdin, "%s", userCommands[3]);

  return 0;
}
