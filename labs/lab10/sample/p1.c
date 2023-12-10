#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;

// May deadlock
void *threadFunction(void *args) {
    sem_wait(&sem1);
    fprintf(stdout, "Thread %ld\n", pthread_self());
    sem_post(&sem1);
}

// Ctrl+C to exit
int main(int argc, char *argv[]){

    sem_init(&sem1, 0, 0);

    pthread_t thd1, thd2;

    pthread_create(&thd1, NULL, (void *)threadFunction, (void*) NULL);
    pthread_create(&thd2, NULL, (void *)threadFunction, (void*) NULL);

    pthread_join(thd1, NULL);
    pthread_join(thd2, NULL);

    return 0;
}