/*
Check p3.c and p4.c
All the required code for the activity is present in the mentioned samples
You will have to work a bit more to figure out certain small details
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// check p3.c for MODE and FLAG macros
#define WRITE (O_WRONLY | O_CREAT | O_TRUNC)
#define PERM (S_IRUSR | S_IWUSR)

int main(int argc, char *argv[]) {
  // accept single argument n and convert to integer
  if (argc != 2) {
    printf("Incorrect number of arguments\n");
    exit(-1);
  }

  int chainLen = atoi(argv[1]);

  int out = open("out.txt", WRITE, PERM);
  if (out == -1) {
    perror("Failed to open file\n");
    exit(-1);
  }

  pid_t pid;
  for (int i = 0; i < chainLen; i++) {  // create process chain
    // declare required variables that must be cloned by child from parent
    // (pipes, character arrays, think about this)
    int fd[2];  // fd[0] = read end; fd[1] = write end
    int ret = pipe(fd);
    if (ret == -1) {
      printf("Error creating pipe\n");
      exit(-1);
    }

    int pids[chainLen];
    pids[i] = getpid();

    // fork
    pid = fork();
    if (pid != 0) {  // parent

      close(fd[0]);

      // parent sends whatever it received + its process ID to child (p4.c)
      for (int j = 0; j < i + 1; j++) {
        write(fd[1], &pids[j], sizeof(int));
        printf("Parent sent %d\n", pids[j]);
      }

      // ensure to close pipe ends properly
      close(fd[1]);

      // wait for child and break
      wait(NULL);
      break;

    } else if (pid == 0) {  // child
      // read data from parent, not that the data size from parent is unknow,
      // you may have to read the pipe in a loop to ensure all data is received

      int nbytes = 0;

      close(fd[1]);

      int j = 0;
      while (nbytes = read(fd[0], &pids[j], sizeof(int)) != 0) {
        printf("Child %d recieved %d -- %d\n", i, pids[j], nbytes);
        j++;
      }
      // ensure to close pipe ends properly
      close(fd[0]);

      // if the current process is the final process
      if (i == chainLen - 1) {
        char strPids[100];
        char temp[12];
        for (int x = 0; x < chainLen; x++) {
          sprintf(temp, "%d ", pids[x]);
          strcat(strPids, temp);
        }

        int TEMP_STDOUT_FILENO = dup(STDOUT_FILENO);
        //      1. redirect STDOUT to out.txt (p3.c) and print the required
        //      result
        if (dup2(out, STDOUT_FILENO) == -1) {
          perror("Failed to redirect output\n");
          exit(-1);
        }

        write(out, strPids, strlen(strPids));
        close(out);

        //      2. restore STDOUT and print the result
        if (dup2(TEMP_STDOUT_FILENO, STDOUT_FILENO) == -1) {
          perror("Failed to restore output\n");
          exit(-1);
        }
        close(TEMP_STDOUT_FILENO);

        printf("\n%s\n", strPids);
      }
    }
  }

  return 0;
}