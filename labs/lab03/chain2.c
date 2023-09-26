#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    // output filename and length of chain as arguments
    if(argc != 3){
        printf("Incorrect number of arguments...\n");
        exit(-1);
    }

    char *filename = argv[1];
    FILE *out = fopen(filename, "a+");
    // store length of chain in a variable
    int chainLen = atoi(argv[2]);

    pid_t pid;

    for (int i = 1; i < chainLen; i++){   
        // spawn processes in a chain manner
        pid = fork();
        // parent process breaks out of loop, child proceeds to next iteration
        if (pid != 0){
            break;
        }
    }

    // parent waits for its child
    waitpid(pid, NULL, 0);
    // get child pid
    pid_t cid = getpid();
    // get parent pid
    pid_t pPid = getppid();
    // write the child pid and parent pid to chain2_out.txt
    // close file after writing
    fprintf(out, "%d -- %d\n", cid, pPid);
    fclose(out);

    return 0;
}

