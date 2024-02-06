/**
 * Title: basicPThread2
 * 
 * Description:
 * The following program shows multiple threads with global and
 * static variables. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details
#include <pthread.h>

//global variable that will change in threads
int g = 0;

//Function to be executed passed to this thread
int * myThreadFun(void * vargp){
    //Store the value argument passed to this thread
    int *myId = (int *)vargp;

    //Create static variable to observe its changes
    static int s = 0;

    //Change static and global variables
    ++s;
    ++g;

    //Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", *myId, ++s, ++g);
}

int main(void){
    int i;
    pthread_t tid;

    //Let us create three threads
    for(i = 0; i < 3; i++){
        pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
    }

    pthread_exit(NULL);
    return EXIT_SUCCESS;
}