/*
Jacob Reed
Operating Systems
University of Washington Tacoma
Autumn 2018
Comments:
Supports unlimited arguments
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <time.h>

#define MAXIN 255
#define SEP "--------------------------------------------------------------------------------"

int currProc = 0;
const char *procStrFin[] = {"First process finished...", "Second process finished...", "Third process finished..."};

struct Response
{
  int pid1;
  int pid2;
  int pid3;
  char *result1;
  char *result2;
  char *result3;
  double time1;
  double time2;
  double time3;
};

//Fork and run command with args
struct Response runCmd(char *command1, char *command2, char *command3, char *file)
{
  struct Response res;
  res.result1 = "";
  res.result2 = "";
  res.result3 = "";

  /*
    Command 1 Parse
    */
  char *fullCommand1 = strcat(command1, " ");
  fullCommand1 = strcat(fullCommand1, file);
  //Create an array of split commands for arg1 of execvp
  char *p1s = strtok(fullCommand1, " ");     //start token pointer
  char *splitCommand1[strlen(fullCommand1)]; //init split command array based on size of full command
  int i1 = 0;                                //init counter
  while (p1s != NULL)                        //Loop through each word and store in array
  {
    splitCommand1[i1++] = p1s;
    p1s = strtok(NULL, " ");
  }
  splitCommand1[i1] = NULL; //NULL terminate array

  /*
    Command 2 Parse
    */
  char *fullCommand2 = strcat(command2, " ");
  fullCommand2 = strcat(fullCommand2, file);
  //Create an array of split commands for arg1 of execvp
  char *p2s = strtok(fullCommand2, " ");     //start token pointer
  char *splitCommand2[strlen(fullCommand2)]; //init split command array based on size of full command
  int i2 = 0;                                //init counter
  while (p2s != NULL)                        //Loop through each word and store in array
  {
    splitCommand2[i2++] = p2s;
    p2s = strtok(NULL, " ");
  }
  splitCommand2[i2] = NULL; //NULL terminate array

  /*
    Command 3 Parse
    */
  char *fullCommand3 = strcat(command3, " ");
  fullCommand3 = strcat(fullCommand3, file);
  //Create an array of split commands for arg1 of execvp
  char *p3s = strtok(fullCommand3, " ");     //start token pointer
  char *splitCommand3[strlen(fullCommand3)]; //init split command array based on size of full command
  int i3 = 0;                                //init counter
  while (p3s != NULL)                        //Loop through each word and store in array
  {
    splitCommand3[i3++] = p3s;
    p3s = strtok(NULL, " ");
  }
  splitCommand3[i3] = NULL; //NULL terminate array

  /*
    FORKS
    */
  double time_spent1 = 0.0;
  double time_spent2 = 0.0;
  double time_spent3 = 0.0;
  clock_t begin = clock();
  clock_t end;

  int p1 = fork();
  if (p1 < 0)
  {
    //Output redirect to file and run command
    int p1file = 0;
    close(STDOUT_FILENO);
    p1file = open("p1.temp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    printf("CMD1:[SHELL 1] STATUS CODE=-1");
  }
  else if (p1 == 0) //P1 Controlled
  {
    //Output redirect to file and run command
    int p1file = 0;
    close(STDOUT_FILENO);
    p1file = open("p1.temp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    execvp(splitCommand1[0], splitCommand1);
  }
  else //Parent Controlled
  {
    end = clock();
    time_spent1 += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s\n", procStrFin[currProc]);
    res.pid1 = p1;
    res.time1 = time_spent1;
    currProc++;
    int p2 = fork();
    if (p2 < 0)
    {
      //Output redirect to file and run command
      int p2file = 0;
      close(STDOUT_FILENO);
      p2file = open("p2.temp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
      printf("CMD2:[SHELL 2] STATUS CODE=-1");
    }
    else if (p2 == 0) //P2 Controlled
    {
      int p2file = 0;
      close(STDOUT_FILENO);
      p2file = open("p2.temp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
      execvp(splitCommand2[0], splitCommand2);
    }
    else //Parent Controlled
    {
      end = clock();
      time_spent2 += (double)(end - begin) / CLOCKS_PER_SEC;
      printf("%s\n", procStrFin[currProc]);
      res.pid2 = p2;
      res.time2 = time_spent2;
      currProc++;
      int p3 = fork();
      if (p3 < 0)
      {
        //Output redirect to file and run command
        int p3file = 0;
        close(STDOUT_FILENO);
        p3file = open("p3.temp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        printf("CMD3:[SHELL 3] STATUS CODE=-1");
      }
      else if (p3 == 0) //P3 Controlled
      {
        int p3file = 0;
        close(STDOUT_FILENO);
        p3file = open("p3.temp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        execvp(splitCommand3[0], splitCommand3);
      }
      else //Parent Controlled
      {
        end = clock();
        time_spent3 += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%s\n", procStrFin[currProc]);
        res.pid3 = p3;
        res.time3 = time_spent3;
        int parent = wait(NULL); //Wait on children
        return res;
      }
    }
  }
}

//Quick max function
float max(float num1, float num2)
{
  return (num1 > num2) ? num1 : num2;
}

/* Take file path and read from file*/
char *readFromFile(char *filename)
{
  char *buffer = NULL;
  int string_size, read_size;
  FILE *file = fopen(filename, "r");

  if (file)
  {
    //Find last byte
    fseek(file, 0, SEEK_END);
    //Get filesize
    string_size = ftell(file);
    rewind(file);
    //Allocate mem
    buffer = (char *)malloc(sizeof(char) * (string_size + 1));
    //Read it
    read_size = fread(buffer, sizeof(char), string_size, file);
    //Add null terminator
    buffer[string_size] = '\0';
    if (string_size != read_size) //Couldn't read in chunk
    {
      free(buffer);
      buffer = NULL;
    }
    fclose(file);
  }
  return buffer;
}

//Deletes file
int deleteFile(char *filename)
{
  if (remove(filename) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//MAIN
int main(int argc, char const *argv[])
{
  char buf[MAXIN];
  //Command 1
  printf("Welcome to MASH!\nmash-1>");
  fgets(buf, MAXIN, stdin);
  buf[strcspn(buf, "\n")] = 0; //remove newlines
  char *cmd1 = strdup(buf);

  //Command 2
  printf("mash-2>");
  fgets(buf, MAXIN, stdin);
  buf[strcspn(buf, "\n")] = 0; //remove newlines
  char *cmd2 = strdup(buf);

  //Command 3
  printf("mash-3>");
  fgets(buf, MAXIN, stdin);
  buf[strcspn(buf, "\n")] = 0; //remove newlines
  char *cmd3 = strdup(buf);

  // File Command
  printf("file>");
  fgets(buf, MAXIN, stdin);
  buf[strcspn(buf, "\n")] = 0; //remove newlines
  char *fileCmd = strdup(buf);

  struct Response response = runCmd(cmd1, cmd2, cmd3, fileCmd);

  //Command Results Output
  int pre = 12;
  int cmd1Len = 80 - (strlen(cmd1) + pre);
  int cmd2Len = 80 - (strlen(cmd2) + pre);
  int cmd3Len = 80 - (strlen(cmd3) + pre);
  char cmd1Sep[80] = "";
  for (int i = 0; i < cmd1Len; i++)
  {
    strcat(cmd1Sep, "-");
  }
  char cmd2Sep[80] = "";
  for (int i = 0; i < cmd2Len; i++)
  {
    strcat(cmd2Sep, "-");
  }
  char cmd3Sep[80] = "";
  for (int i = 0; i < cmd3Len; i++)
  {
    strcat(cmd3Sep, "-");
  }

  //Get file input
  char *cmd1Out = readFromFile("p1.temp");
  char *cmd2Out = readFromFile("p2.temp");
  char *cmd3Out = readFromFile("p3.temp");

  //Delete Files
  deleteFile("p1.temp");
  deleteFile("p2.temp");
  deleteFile("p3.temp");

  printf("-----CMD 1: %s%s\n", cmd1, cmd1Sep);
  printf("%sResult took:%fms\n", cmd1Out, response.time1);
  printf("-----CMD 2: %s%s\n", cmd2, cmd2Sep);
  printf("%sResult took:%fms\n", cmd2Out, response.time2);
  printf("-----CMD 3: %s%s\n", cmd3, cmd3Sep);
  printf("%sResult took:%fms\n", cmd3Out, response.time3);
  printf("%s\n", SEP);
  printf("Children process IDs: %d %d %d.\n", response.pid1, response.pid2, response.pid3);
  printf("Total elapsed time:%fms\n", max(response.time3, max(response.time2, response.time1)));
  return 0;
}
