#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;

// May deadlock
void *threadFunction1(void *args) {
    sem_wait(&sem1);
    sem_wait(&sem2);
    fprintf(stdout, "Thread %ld with sem1 - sem2\n", pthread_self());
    sem_post(&sem2);
    sem_post(&sem1);
}

void *threadFunction2(void *args) {
    sem_wait(&sem2);
    sem_wait(&sem1);
    fprintf(stdout, "Thread %ld with sem2 - sem1\n", pthread_self());
    sem_post(&sem1);
    sem_post(&sem2);
}

int main(int argc, char *argv[]){

    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);

    pthread_t thd1, thd2;

    pthread_create(&thd1, NULL, (void *)threadFunction1, (void*) NULL);
    pthread_create(&thd2, NULL, (void *)threadFunction2, (void*) NULL);

    pthread_join(thd1, NULL);
    pthread_join(thd2, NULL);

    return 0;
}