#include <iostream>
#include <vector>
#include <chrono> 
#include <cstdlib>
#include <ctime>  
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    }
}

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000; 
    }
    return arr;
}

void analyzePerformance(const vector<int>& inputSizes) {
    for (int size : inputSizes) {
        vector<int> arr = generateRandomArray(size);

        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed = end - start;
        cout << "Array Size: " << size << "| Execution Time: " << elapsed.count() << " seconds\n";
    }
}

int main() {
    srand(time(nullptr)); 

    vector<int> inputSizes = {1000, 5000, 10000, 50000, 100000};

    cout << "Quick Sort Performance Analysis:\n";
    analyzePerformance(inputSizes);

    return 0;
}

// TC = O(n log n) 
// SC = o(n)  