// Graceful exit on Ctrl + C
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int loop = 1;

void ctrlcHandler(int signo){
    fprintf(stdout, "Set loop\n");
    fflush(stdout);
    loop = 0;
}

int main(int argc, char *argv[]) {
    
    struct sigaction action;
    action.sa_handler = ctrlcHandler;
    action.sa_flags = 0;

    if((sigemptyset(&action.sa_mask) == -1) || // clear all signals
        (sigaction(SIGINT, &action, NULL) == -1)) // set signal handler
        perror("Error setting signal handler for Ctrl + C...\n");
    
    int counter = 0;
    while(loop){
        fprintf(stdout, "counter: %d\n", counter++);
        fflush(stdout);
        sleep(1);
    }

    fprintf(stdout, "Graceful exit...\n");
    fflush(stdout);
    return 0;
}