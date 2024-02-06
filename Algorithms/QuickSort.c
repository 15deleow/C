#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void quickSort(int [], int, int);
int partition(int [], int, int);
void testRandomOrderArray();
int isSorted(int arr[], int n);
void testSortedArray();
void testReverseSortedArray();
void testRandomOrderArray();
void testEmptyArray();
void swap(int * xp, int * yp);

int main(void){
    testSortedArray();
    testReverseSortedArray();
    testRandomOrderArray();
    testEmptyArray();

    return EXIT_SUCCESS;
}

int isSorted(int arr[], int n){
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // Not sorted
        }
    }
    return 1; // Sorted
}

// Test Case 1: Sort an already sorted array
void testSortedArray() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    printf("[Test Case 1] Sort a sorted array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

// Test Case 2: Sort an array in reverse order
void testReverseSortedArray() {
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    printf("[Test Case 2] Sort an array in reverse order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

// Test Case 3: Sort an array with random order
void testRandomOrderArray() {
    int arr[] = {3, 1, 4, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);
    printf("[Test Case 3] Sort an array with random order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

// Test Case 4: Sort an empty array
void testEmptyArray() {
    int arr[] = {};
    int n = 0;

    quickSort(arr, 0, n - 1);
    printf("[Test Case 4] Sort an empty array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void quickSort(int arr[], int start, int end){
    //When start value meets the end value, stop recursion
    if(start < end){
        //Split array into two parts
        //Modified that one side has values less than the pivot
        //and the other side has values greater
        //returns the index where the partition occurs
        int partitionIndex = partition(arr, start, end);

        //Recursively sort the elements before and after the partition
        quickSort(arr, start, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, end);
    }
}

int partition(int arr[], int start, int end){
    //Pivot is the last element in array
    int pivot = arr[end];
    int i = start - 1;

    //Iterate through array starting from index start
    //to index end - 1.
    for(int j = start; j <= end - 1; j++){
        //If the current value is less than the pivot value
        //increment i
        //Swap the value at index i with the value at index j
        if(arr[j] < pivot){
            i++;
            
            //Swap arr[i] and arr[j]
            swap(&arr[i], &arr[j]);
        }
    }  

    //Swap the value at index i + 1 with the value at index high
    //places the pivot at the correct position
    swap(&arr[i + 1], &arr[end]);

    //Return the partition index
    return i + 1;
}

void swap(int * xp, int * yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}