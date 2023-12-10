// Block and unblock Ctrl-Z
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// Call Ctrl-Z before counter reacher 5
// After counter is 5, the program will be suspended
// You will have to manually call kill %1 in the terminal, where 1 is the number shown to the left of suspended output in the terminal
// [1]  + 183029 suspended  ./main
int main(int argc, char *argv[]) {
    sigset_t set;

    if((sigemptyset(&set) == -1) || // clear set
        (sigaddset(&set, SIGTSTP) == -1)) { // set SIGTSTP in set
            perror("Failed to set SIGTSTP");
            return -1;
        }
    
    if(sigprocmask(SIG_BLOCK, &set, NULL) == -1) { // configure to block SIGTSTP (Ctrl - Z)
        perror("Failed to block signal mask");
        return -1;
    }

    int counter = 0;
    while(1) {
        fprintf(stdout, "counter: %d\n", counter++);
        fflush(stdout);

        if(counter == 5){
            if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1) { // unblock Ctrl-Z
                perror("Failed to unblock signal mask");
                return -1;
            }       
        }
        sleep(2);
    }
    return 0;
}