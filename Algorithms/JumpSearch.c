#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define NOT_FOUND -1

int jumpSearch(int [],int,int);
void jumpSearch_TargetNotInList_NotFoundReturned();
void jumpSearch_TargetInList_CorrectIndexReturned();


int main(void){
    jumpSearch_TargetNotInList_NotFoundReturned();
    jumpSearch_TargetInList_CorrectIndexReturned();
    return EXIT_SUCCESS;
}

int jumpSearch(int arr[], int arrSize, int target){
    //Calculate the size of the jump
    int step = sqrt(target);
    //Initialize variable to keep track of the prev position
    int prev = 0;

    /* Step through the array until it finds a section of the
    Array where the value at the last index is greater than or
    equal to the target value. 
    */
    while(arr[(int)fmin(step, arrSize) - 1] < target){
        //Save current jump size and calculate new jump size
        prev = step;
        step += sqrt(arrSize);

        //If the last jump size is greater than or equal to the
        //array size, the target is not found in the array.
        if(prev >= arrSize){
            return NOT_FOUND;
        }
    }

    //Starting from index prev, search the array for the target value
    while(arr[prev] != target){
        prev++;
        //if prev reaches the end of the array
        //target is not in the array
        if(prev == arrSize){
            return NOT_FOUND;
        }
    }

    return prev;
}

void jumpSearch_TargetNotInList_NotFoundReturned(){
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 11;

    printf("[Test Case 1] Target is not in the list: ");
    assert(jumpSearch(arr, n, target) == NOT_FOUND);
    printf("PASS\n");
}

void jumpSearch_TargetInList_CorrectIndexReturned(){
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4, expectedIndex = 4;

    printf("[Test Case 2] Target is in the list: ");
    assert(jumpSearch(arr, n, target) == expectedIndex);
    printf("PASS\n");
}