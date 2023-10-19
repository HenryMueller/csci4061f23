#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);

    // Create an MxN matrix using dynamic allocation
    
    // Bug alert
    // Hint: create m rows, then allocate n memory locations per row
    int **mat = (int **)malloc(sizeof(int *) * M );

    for(int i = 0; i < M; i++){
        mat[i] = (int *) malloc(sizeof(int) * N);
        for(int j = 0; j < N; j++){
            mat[i][j] = i + j;
        }
    }

    // create another MxN matrix matcopy which stores negative values of mat
    // matcopy[i][j] = -mat[i][j]
    
    // Bug alert
    // Hint: Memory allocation similar to mat
    int **matcopy = (int **)malloc(sizeof(int *) * M );

    for(int i = 0; i < M; i++){
        matcopy[i] = (int *) malloc(sizeof(int) * N);
        for(int j = 0; j < N; j++){
            matcopy[i][j] = 0 - (i + j);
        }
    }
    


    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", mat[i][j] + matcopy[i][j]); // zero
        }
        printf("\n");
    }

    // free memory for mat and matcopy
    // Hint: Free each row then the entire matrix. Don't forget a final NULL assignment.
    for (int i = 0; i < M; i++) {
        free(mat[i]);
        free(matcopy[i]);
    }
    free(mat);
    free(matcopy);

    return 0;
}