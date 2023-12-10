#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;

// Allows only 5 threads to enter at a time
void *threadFunction(void *args) {
    sem_wait(&sem1);
    fprintf(stdout, "Thread %ld\n", pthread_self());
    sleep(1);
    sem_post(&sem1);
}

int main(int argc, char *argv[]){

    sem_init(&sem1, 0, 5);

    pthread_t thds[10];

    for(int i = 0;  i < 10; i++)
        pthread_create(&thds[i], NULL, (void *)threadFunction, (void *)NULL);

    for(int i = 0; i <10; i++)
        pthread_join(thds[i], NULL);

    return 0;
}