#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 5000

void Merge(int arr[], int left, int mid, int right){
    int i,j,k;
    int n1 = mid-left+1;
    int n2 = right-mid;
    int L[n1],M[n2];

    for(int i=0; i<n1; i++)
    L[i]= arr[left+i];
    for(int j=0; j<n2; j++)
    M[j]= arr[mid+1+j];

    i=0;
    j=0;
    k=left;

    while(i<n1 && j<n2){
        if(L[i] <= M[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = M[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x)
            return mid;
        if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void generateRandomArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 20 == 0)
            printf("\n");
    }
    printf("\n");
}

int main() {
    int arr[SIZE];
    int key, choice;
    generateRandomArray(arr, SIZE);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Display Array\n");
        printf("2. Sort Array\n");
        printf("3. Search for an Element\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayArray(arr, SIZE);
                break;
            case 2:
                MergeSort(arr, 0, SIZE - 1);
                printf("Sorted array:\n");
                displayArray(arr, SIZE);
                break;
            case 3:
                printf("Enter the element to search: ");
                scanf("%d", &key);
                int result = binarySearch(arr, 0, SIZE - 1, key);
                if (result != -1)
                    printf("Element found at index %d.\n", result);
                else
                    printf("Element not found.\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// TC = O(n log n) or o(n^2)(worst case)
// SC = o(n) 