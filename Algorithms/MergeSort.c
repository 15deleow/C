#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum boolean {TRUE = 1, FALSE = 0};

int isSorted(int arr[], int n);
void testSortedArray();
void testReverseSortedArray();
void testRandomOrderArray();
void testEmptyArray();
void mergeSort(int [], int, int);
void merge(int [], int, int, int);
void copyArray(int [], int [], int, int);

void printArray(int arr[], int arrSize){
    for(int i = 0; i < arrSize; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void){
    printf("========= Testing MergeSort Algorithm =========\n\n");

    testSortedArray();
    testReverseSortedArray();
    testRandomOrderArray();
    testEmptyArray();

    return EXIT_SUCCESS;
}

void mergeSort(int arr[], int left, int right){
    int middle;

    if(left < right){
        //Find the middle index of the array, avoids overflow
        middle = left + (right - left) / 2;

        //LeftSide
        mergeSort(arr, left, middle);
        //Right Side
        mergeSort(arr, middle + 1, right);

        //Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

void merge(int arr[], int left, int middle, int right){
    //Calculate size of temp arrays
    int leftArraySize = middle - left + 1;
    int rightArraySize = right - middle;

    //Create temp arrays
    int leftArray[leftArraySize];
    int rightArray[rightArraySize];

    //Copy data from original array to temp arrays
    copyArray(arr, leftArray, leftArraySize, left);
    copyArray(arr, rightArray, rightArraySize, middle + 1);

    // Merge the two halves back into the original array
    int i = 0, j = 0, k = left;
    while(i < leftArraySize && j < rightArraySize){
        //Compare values, smaller value gets added to original array
        if(leftArray[i] <= rightArray[j]){
            arr[k++] = leftArray[i++];
        }else{
            arr[k++] = rightArray[j++];
        }
    }

    //Copy the remaning elements from temp arrays, if any
    while(i < leftArraySize){
        arr[k++] = leftArray[i++];
    }

    while(j < rightArraySize){
        arr[k++] = rightArray[j++];
    }
}

void copyArray(int arr[], int tempArr[], int tempSize, int offset){
    for(int i = 0; i < tempSize; i++){
        //Copy data from arr starting at an index offset to tempArr
        tempArr[i] = arr[offset + i];
    }
}

//Test Methods
int isSorted(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        if(arr[i] > arr[i + 1]){
            return 0;
        }
    }
    return 1;
}

void testSortedArray(){
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, n - 1);

    printf("[Test Case 1] Sort a sorted array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void testReverseSortedArray(){
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, n - 1);

    printf("[Test Case 2] Sort an array in reverse order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void testRandomOrderArray(){
    int arr[] = {3, 1, 4, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, n - 1);

    printf("[Test Case 3] Sort an array with random order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void testEmptyArray(){
    int arr[] = {};
    int n = 0;

    mergeSort(arr, 0, n - 1);

    printf("[Test Case 4] Sort an empty array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}