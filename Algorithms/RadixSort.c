#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int findMaxDigits(int [], int);
void countingSort(int [], int, int);
void radixSort(int [], int n);
int isSorted(int arr[], int n);
void testSortedArray();
void testReverseSortedArray();
void testRandomOrderArray();
void testEmptyArray();

int main(void){
    testSortedArray();
    testReverseSortedArray();
    testRandomOrderArray();
    testEmptyArray();

    return EXIT_SUCCESS;
}

void radixSort(int arr[], int arrSize){
    int exp = 1;
    int maxDigits = findMaxDigits(arr, arrSize);

    // Perform counting sort for each digit position
    // Starting at the 1's place, incrementing by multiple of 10
    // Loops until i reaches maxDigits, number of passes to make
    for (int i = 0; i < maxDigits; i++) {
        //Sorts the array based on the current digit
        countingSort(arr, arrSize, exp);
        //Move to the next place in value
        exp *= 10;
    }
}

void countingSort(int arr[], int arrSize, int exp){
    const int radix = 10;
    int output[arrSize];
    int * count = calloc(sizeof(int), radix);

    //Count occurrences of digits at the current position
    for(int i = 0; i < arrSize; i++){
        //arr[i] / exp isolates the digit
        // % radix ensures digit falls between [0, radix)
        //Result maps the digit to an index in count
        //increment the value pointed by the calculated index 
        count[(arr[i] / exp) % radix]++;
    }

    //Modify count[] to store the position of the digit in output
    //count[i] after a loop will represent the count of elements
    //with a digit less than or equal to i
    for(int i = 1; i < radix; i++){
        count[i] += count[i - 1];
    }

    // Build the output array
    for(int i = arrSize - 1; i >= 0; i--){
        //calculate the digit at the current radix position for the element i
        //and use it as the index to get the cumulative count info in the count array
        //assign value at index i in arr and assign to output
        output[count[(arr[i] / exp) % radix] - 1] = arr[i];

        // //decrement the count for the specific digit in the count array
        count[(arr[i] / exp) % radix]--;
    }

    //copy the output array to arr[]
    for(int i = 0; i < arrSize; i++){
        arr[i] = output[i];
    }

    free(count);
}

int findMaxDigits(int arr[], int arrSize){
    int maxDigits = 1;

    //Interate through the array
    for(int i = 0; i < arrSize; i++){
        //Record the current value at i
        int num = arr[i];
        int currentDigits = 0;

        //Count the number of digits
        //that makes up the value assigned to num
        while(num > 0){
            currentDigits++;
            num /= 10;
        }

        //If the number of values counted is greater than
        //the current maxDigits value, update maxDigits
        if(currentDigits > maxDigits){
            maxDigits = currentDigits;
        }
    }

    return maxDigits;
}

int isSorted(int arr[], int n){
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // Not sorted
        }
    }
    return 1; // Sorted
}

void testSortedArray(){
    int arr[] = {17, 26, 42, 55, 93};
    int n = sizeof(arr) / sizeof(arr[0]);

    radixSort(arr, n);

    printf("[Test Case 1] Sort a sorted array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void testReverseSortedArray(){
    int arr[] = {93, 55, 42, 26, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    radixSort(arr, n);

    printf("[Test Case 2] Sort an array in reverse order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void testRandomOrderArray(){
    int arr[] = {42, 17, 93, 26, 55};
    int n = sizeof(arr) / sizeof(arr[0]);

    radixSort(arr, n);

    printf("[Test Case 3] Sort an array with random order: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}

void testEmptyArray(){
    int arr[] = {};
    int n = 0;

    radixSort(arr, n);

    printf("[Test Case 4] Sort an empty array: ");
    assert(isSorted(arr, n));
    printf("Passed\n");
}
