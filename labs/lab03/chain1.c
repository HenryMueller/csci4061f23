#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Incorrect number of arguments...\n");
        exit(-1);
    }

    // store length of chain in a variable
    int chainLen = atoi(argv[1]);

    pid_t parent_id = getpid();
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

    // get pid and convert to character array
    // use sprintf
    char cid[48];
    sprintf(cid, "%d", getpid());

    // get ppid and convert to character array
    // use sprintf
    char pPid[48];
    sprintf(pPid, "%d", getppid());

    // use execl or execv to pass the process ids to echo
    // echo path: /bin/echo
    execl("/bin/echo", "echo", cid, " -- ", pPid, NULL);

    

    return 0;
}

