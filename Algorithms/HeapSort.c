#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int isSorted(int arr[], int n);
void testSortedArray();
void testReverseSortedArray();
void testRandomOrderArray();
void testEmptyArray();
void heapSort(int [], int);
void heapify(int [], int, int);
void swap(int *, int *);

void printArray(int arr[], int arrSize){
    for(int i = 0; i < arrSize; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void){
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    return EXIT_SUCCESS;
}

void heapSort(int arr[], int n){
    //Build max heap, starting from last non-leaf node
    //n / 2 - 1 is the index of the last non-leaf node
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }

    printArray(arr, n);

    // Extract elements one by one from the heap
    for(int i = n - 1; i > 0; i--){
        //Move the current root to the end
        swap(&arr[0], &arr[i]);

        //Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i){
    //Initialize to the root
    int largest = i;

    //Equation to find left and right child nodes
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //If the left child is larger than root
    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }

    //If the right child is larger than the root
    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }

    //If largest is not root, swap and recursively heapify the affected sub-tree
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}