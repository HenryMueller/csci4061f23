#include <stdio.h>
#include <pthread.h>

void *display(void *arg){
    char *data = (char *)arg;
    printf("%ld -- %s\n", pthread_self(), data);
}

int main(int argc, char *argv[]){
    pthread_t arg1_thread;
    pthread_t arg2_thread;

    // create two threads
    pthread_create(&arg1_thread, NULL, (void*)display, (void*)argv[1]);
    pthread_create(&arg2_thread, NULL, (void*)display, (void*)argv[2]);

    // join the two threads
    pthread_join(arg1_thread, NULL);
    pthread_join(arg2_thread, NULL);

    return 0;
}