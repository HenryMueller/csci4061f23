#include<stdio.h>
#include <stdlib.h>
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
    
    // cast return value to void *
    return (void*)(sum);
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
    }

    void *ret;
    for(int i = 0; i < t; i++){
        // join thread and print returned value
        pthread_join(thd[i], &ret);
        printf("Thread %d - %d\n", i, *((int*)ret));
        free(ret);
        ret = NULL;
    }

    return 0;
}