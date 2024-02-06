#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define NOT_FOUND -1

int interpolationSearch(int [], int, int);
int interpolationSearch_ItemNotInList_NotFound();
int interpolationSearch_ItemInFront_CorrectIndex();
int interpolationSearch_ItemAtEnd_CorrectIndex();

int main(void){
    interpolationSearch_ItemNotInList_NotFound();
    interpolationSearch_ItemInFront_CorrectIndex();
    interpolationSearch_ItemAtEnd_CorrectIndex();

    return EXIT_SUCCESS;
}

int interpolationSearch_ItemNotInList_NotFound(){
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 110;

    //Execute Interpolation Search
    printf("[Test Case 1] Item not in list: ");
    assert(interpolationSearch(arr, n, x) == NOT_FOUND);
    printf("PASS\n");
}

int interpolationSearch_ItemInFront_CorrectIndex(){
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    int expectedIndex = 0;

    //Execute Interpolation Search
    printf("[Test Case 2] Item located at the start: ");
    assert(interpolationSearch(arr, n, x) == expectedIndex);
    printf("PASS\n");
}

int interpolationSearch_ItemAtEnd_CorrectIndex(){
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 100;
    int expectedIndex = 9;

    //Execute Interpolation Search
    printf("[Test Case 3] Item located at the end: ");
    assert(interpolationSearch(arr, n, x) == expectedIndex);
    printf("PASS\n");
}

int interpolationSearch(int arr[], int arrSize, int target){
    int start = 0, end = arrSize - 1;

    while(start <= end && target >= arr[start] && target <= arr[end]){
        //Only one item in array, simple check
        if(start == end){
            if(arr[start] == target){
                return start;
            }
            return -1;
        }

        //Calculate the position of the target value using interpolation formula
        int pos = start + ((double)(end - start) / (arr[end] - arr[start])) * (target - arr[start]);
        if(arr[pos] == target){
            return pos;
        }else if(arr[pos] < target){
            start = pos + 1;
        }else{
            end = pos - 1;
        }
    }

    return -1;
}