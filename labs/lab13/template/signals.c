// Block and unblock Ctrl-Z
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int loop = 1;

// create SIGINT Handler - pgm1.c
???

int main(int argc, char *argv[]) {
    struct sigaction action;

    // use action.sa_mask instead of set variable - pgm2.c
    if((sigemptyset(&action.sa_mask) == -1)|| // clear set
        (???) || // add SIGINT to mask
        (sigaction(SIGINT, &action, NULL) == -1)) { // set SIGINT sigaction
            perror("Failed to set SIGINT");
            return -1;
        }
    
    if(???) { // block SIGINT (Ctrl - C)
        perror("Failed to block signal mask");
        return -1;
    }

    int counter = 1;
    while(loop) {
        fprintf(stdout, "counter: %d\n", counter);
        fflush(stdout);

        if(counter == 5){
            if(???) { // unblock Ctrl-C
                perror("Failed to unblock signal mask");
                return -1;
            }       
        }
        counter++;
        sleep(2);
    }
    fprintf(stdout, "Gracefully exiting...\n");
    return 0;
}