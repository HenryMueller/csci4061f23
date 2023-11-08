#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct Arguments{
    int *arr;
    int start;
    int end;
    int n;
};

typedef struct Arguments Args;

void *summation(void *arg){
    Args *args = (Args *)arg;
    int *sum = (int*)malloc(sizeof(int));
    *sum = 0;
    for(int i = args->start; i < args->end; i++)
        *sum += args->arr[i];
    
    printf("%d\n", *sum);
    free(sum);
    return (void*) NULL;
}
int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    int t = atoi(argv[2]);
    int arr[n];
    for(int i = 0; i < n;  i++)
        arr[i] = i;
    
    pthread_t thd[t];
    Args t_args[t];

    int div = n / t;
    for(int i = 0; i < t; i++){
        // arguments per thread
        t_args[i].arr = arr;
        t_args[i].start = i * div;
        t_args[i].end = t_args[i].start + div;
        t_args[i].n = n;

        // create thread
        pthread_create(&thd[i], NULL, (void *)summation, (void *)&t_args[i]);
        pthread_detach(thd[i]);
    }

    // if sleep is not called, as soon as the main process exits all the spawned threads will also exit without completion
    sleep(2);
    return 0;
}