/**
 * Title: basicPThread
 * 
 * Description:
 * The following program is a simple program to demonstrate use of
 * pthread basic functions. Creates a thread that will display a string
 * after delaying for 1 second.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details
#include <pthread.h>

//A Normal C function that is executed as a thread
//When its name is specified in pthread_create()
void *myThreadFun(void *vargp){
    sleep(1);
    printf("Printing GeeksQuiz from Thread\n");
    return NULL;
}

int main(void){
    //Used to identify the thread in the system
    pthread_t thread_id;
    printf("Before Thread\n");

    //Create a thread that will run the myThreadFun method
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    
    //equivalent of wait() in processess
    //blocks the calling thread until the the thread with
    //identifier equal to thread_id, terminates
    pthread_join(thread_id, NULL);

    printf("After Thread\n");
    return EXIT_SUCCESS;
}