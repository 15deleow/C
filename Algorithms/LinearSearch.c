#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NOT_FOUND -1

int linearSearch(int [], int, int);
void testTargetAtTheStart();
void testTargetAtTheEnd();
void testNonExistingTarget();
void testEmptyArray();

int main(void){
    testTargetAtTheStart();
    testTargetAtTheEnd();
    testNonExistingTarget();
    testEmptyArray();

    return EXIT_SUCCESS;
}

int linearSearch(int arr[], int arrSize, int target){
    for(int i = 0; i < arrSize; i++){
        if(arr[i] == target){
            return i;
        }
    }

    return NOT_FOUND;
}

void testTargetAtTheStart(){
    int arr[] = {93, 55, 42, 26, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 93;

    int targetIndex = linearSearch(arr, n, target);

    printf("[Test 1] Target is found at the start: ");
    assert(linearSearch(arr, n, target) == 0);
    printf("Pass\n");
}

void testTargetAtTheEnd(){
    int arr[] = {93, 55, 42, 26, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 17;

    int targetIndex = linearSearch(arr, n, target);

    printf("[Test 2] Target is found at the end: ");
    assert(linearSearch(arr, n, target) == 4);
    printf("Pass\n");
}

void testNonExistingTarget(){
    int arr[] = {93, 55, 42, 26, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 5;

    printf("[Test 3] Target is not in the array: ");
    assert(linearSearch(arr, n, target) == NOT_FOUND);
    printf("Pass\n");
}

void testEmptyArray(){
    int arr[] = {};
    int n = 0;
    int target = 5;

    printf("[Test 4] Empty Array: ");
    assert(linearSearch(arr, n, target) == NOT_FOUND);
    printf("Pass\n");
}