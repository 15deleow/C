#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NOT_FOUND -1

int binarySearch(int[], int, int, int);
int binarySearchR(int[], int, int, int);
void testTargetPresent();
void testSingleElementList();
void testNonExistingTarget();
void testEmptyArray();

int main(void){
    testTargetPresent();
    testSingleElementList();
    testNonExistingTarget();
    testEmptyArray();

    //Recursive Version
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("[] Recursive Version Test: ");
    assert(binarySearchR(arr, 0, n-1, 9) == 4);
    printf("Pass\n");
    return EXIT_SUCCESS;
}

int binarySearch(int arr[], int start, int end, int target){
    while(start <= end){
        int mid = start + (end - start) / 2;
        if(arr[mid] == target){
            return mid;
        }else if(target < arr[mid]){
            end = mid - 1;
        }else if(target > arr[mid]){
            start = mid + 1;
        }
    }

    return NOT_FOUND;
}

int binarySearchR(int arr[], int start, int end, int target){
    if(start > end) return NOT_FOUND;

    int mid = start + (end - start) / 2;

    if(arr[mid] == target){
        return mid;
    }else if(target < arr[mid]){
        binarySearchR(arr, start, mid - 1, target);
    }else{
        binarySearchR(arr, mid + 1, end, target);
    }
}

void testTargetPresent(){
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 20;

    printf("[Test 1] Target is present: ");
    assert(binarySearch(arr, 0, n - 1, target) == 9);
    printf("Pass\n");
}

void testSingleElementList(){
    int arr[] = {20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 20;

    printf("[Test 2] Search Targert in a single element array: ");
    assert(binarySearch(arr, 0, n - 1, target) == 0);
    printf("Pass\n");
}

void testNonExistingTarget(){
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 5;

    printf("[Test 3] Target is not in the array: ");
    assert(binarySearch(arr, 0, n - 1, target) == NOT_FOUND);
    printf("Pass\n");
}

void testEmptyArray(){
    int arr[] = {};
    int n = 0;
    int target = 5;

    printf("[Test 4] Empty Array: ");
    assert(binarySearch(arr, 0, n - 1, target) == NOT_FOUND);
    printf("Pass\n");
}