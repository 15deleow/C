#include <stdio.h>
#include <stdlib.h>

//Prototype
void printArray(int *, int);
void insertionSort(int [], int);

int main(void){
    int arr[] = {12, 11, 13, 5, 6};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: ");
    printArray(arr, arrSize);

    // Call Insertion Sort
    insertionSort(arr, arrSize);

    printf("Sorted array: ");
    printArray(arr, arrSize);
    return EXIT_SUCCESS;
}

// Function to print an array
void printArray(int arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int arrSize){
    int key, j;

    //Iterate through the unsorted list
    for(int i = 1; i < arrSize; i++){
        //Current element to be inserted
        key = arr[i];
        j = i;    

        //Compare key with elements in the sorted list and shift as needed
        while(j > 0 && arr[j - 1] > key){
            arr[j] = arr[j - 1];
            j--;
        }

        //Insert the key at its correct position in the sorted list
        arr[j] = key;
    }
}