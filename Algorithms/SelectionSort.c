#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void swap(int *, int *);
void selectionSort(int [], int arrSize);
int isSorted(int *, int n);
void testSortedArray();
void testRandomOrderArray();
void testReverseSortedArray();
void testEmptyArray();
void printArray(int arr[], int arrSize);


int main(void){

    testSortedArray();
    testRandomOrderArray();
    testReverseSortedArray();
    testEmptyArray();

    

    return EXIT_SUCCESS;
}

void printArray(int arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to check if an array is sorted
int isSorted(int arr[], int n) {
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

    selectionSort(arr, n);

    printf("[Test Case 1] Sort a sorted array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

// Test Case 2: Sort an array in reverse order
void testReverseSortedArray() {
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, n);

    printf("[Test Case 2] Sort an array in reverse order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

// Test Case 3: Sort an array with random order
void testRandomOrderArray() {
    int arr[] = {3, 1, 4, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, n);
    printf("[Test Case 3] Sort an array with random order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

// Test Case 4: Sort an empty array
void testEmptyArray() {
    int arr[] = {};
    int n = 0;

    selectionSort(arr, n);
    printf("[Test Case 4] Sort an empty array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void selectionSort(int arr[], int arrSize){
    int min;

    for(int i = 0; i < arrSize - 1; i++){
        //At each index, starts with the current value as the min
        min = i;

        //FInd the index of the minimum element in the unsorted part
        for(int j = i + 1; j < arrSize; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }

        //Swap the found minimum element with the first element
        swap(&arr[min], &arr[i]);
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}