/**
 * Title: integerMatrixThreads
 * 
 * Description:
 * The following program builds a large matrix of unsigned integer values.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details
#include <pthread.h>

#define NUM_THREADS 8
#define MAX_LENGTH 40000
#define CHUNK_SIZE (MAX_LENGTH / NUM_THREADS) * 2

struct arg_struct{
    int start;
    int end;
    int threadId;
};

void longRunningTask(unsigned start, unsigned end, unsigned chunk);
void * createThread(void * args);

void * createThread(void * args){
    struct arg_struct * vals = args;
    longRunningTask(vals->start, vals->end, MAX_LENGTH / NUM_THREADS);
    pthread_exit(NULL);
}

void longRunningTask(unsigned start, unsigned end, unsigned chunk){
    //Create 2D array of unsigned values
    unsigned * matrix = malloc(chunk * chunk * sizeof(unsigned));

    if(matrix == NULL){
        return;
    }

    int index = 0;
    for(int i = start; i < end; i++){
        for(int u = start; u < end; u++){
            matrix[index++] = i * u;
        }
    }

    free(matrix);
}

int main(int argc, char * argv[]){
    //Sequential execution
    longRunningTask(0, MAX_LENGTH, MAX_LENGTH * MAX_LENGTH);

    //Parallel Execution
    pthread_t threads[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++){
        int start = i * CHUNK_SIZE;
        int end = (start + CHUNK_SIZE) - 1;

        struct arg_struct thread_args;
        thread_args.start = start;
        thread_args.end = end;
        thread_args.threadId = i;

        int rc = pthread_create(&threads[i], NULL, createThread, (void *)&thread_args);
        if(rc)
            return -1;
    }

    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}