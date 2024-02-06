#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void swap(int *, int *);
void bubbleSort(int *, int);
int isSorted(int *, int n);
void testSortedArray();
void testRandomOrderArray();
void testReverseSortedArray();
void testEmptyArray();

int main(void){
    // Run the tests
    testSortedArray();
    testReverseSortedArray();
    testRandomOrderArray();
    testEmptyArray();

    printf("All tests passed successfully!\n");

    return EXIT_SUCCESS;
}

// Test Case 1: Sort an already sorted array
void testSortedArray() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    assert(isSorted(arr, n));
}

// Test Case 2: Sort an array in reverse order
void testReverseSortedArray() {
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    assert(isSorted(arr, n));
}

// Test Case 3: Sort an array with random order
void testRandomOrderArray() {
    int arr[] = {3, 1, 4, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    assert(isSorted(arr, n));
}

// Test Case 4: Sort an empty array
void testEmptyArray() {
    int arr[] = {};
    int n = 0;

    bubbleSort(arr, n);

    assert(isSorted(arr, n));
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

void bubbleSort(int * arr, int arrSize){
    for(int i = 0; i < arrSize - 1; i++){
        //Compare adjacent elements, avoiding elements that
        //have already been correctly placed
        for(int j = 0; j < arrSize - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void swap(int * xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}