#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    if(argc != 2){ // There should only one input argument, otherwise error out
        printf("There should only be one input");
        return -1;
    }

    // use atoi to convert argv[1] to integer and store in n_procs
    int n_procs = atoi(argv[1]);

    pid_t pid;
    for(int i = 1; i <= n_procs; i++){
        pid = fork();
        // after child is spawned, the parent continues with the loop and the child breaks out of the loop
        if (pid == 0){
            break;
        }
    }
    
    // print the child id and the parent id
    printf("Child ID: [%d] --- Parent ID: [%d]\n", getpid(), getppid());

    return 0;
}

