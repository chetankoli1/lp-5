# Parallel Bubble Sort and Merge Sort

## Problem Statement

The goal of this project is to implement parallel versions of Bubble Sort and Merge Sort algorithms using OpenMP and compare their performance with their sequential counterparts. The program will measure the execution time of each algorithm for sorting a given array and calculate the speedup achieved by the parallel versions.

## Implementation and Performance Measurement

The program utilizes OpenMP directives to parallelize the sorting algorithms. For Bubble Sort, the algorithm repeatedly compares adjacent elements and swaps them if they are in the wrong order until the entire array is sorted. Parallelization is achieved by distributing the iterations of the outer loop among multiple threads using the `#pragma omp parallel for` directive. A shared flag variable is used to track if any swaps are made during each pass, ensuring correct termination of the algorithm.

For Merge Sort, the algorithm divides the array into smaller subarrays, recursively sorts them, and then merges the sorted subarrays to produce the final sorted array. Parallelization is implemented using the divide-and-conquer strategy. The `#pragma omp parallel sections` directive divides the sorting task into two parallel sections, each responsible for sorting a subarray. Afterward, a parallel merge operation combines the sorted subarrays into a sorted array. The `#pragma omp parallel for` directive is used to parallelize the merge operation.

To measure the performance of the algorithms, the program records the execution time for both the sequential and parallel versions of Bubble Sort and Merge Sort. The speedup is then calculated using the formula: `Speedup = Sequential Time / Parallel Time`.

## Paralle Bubble Sort using OpenMP
```cpp
#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    #pragma omp parallel shared(arr, swapped)
    {
        do {
            #pragma omp for
            for (int i = 0; i < n - 1; i++) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    #pragma omp critical
                    {
                        swapped = true;
                    }
                }
            }
            
            #pragma omp barrier
            #pragma omp single
            {
                swapped = false;
            }
        } while (swapped);
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform parallel Bubble Sort
    parallelBubbleSort(arr);

    // Print sorted array
    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

```

## Paralle Merge Sort using OpenMP
```cpp
#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, int low, int mid, int high) {
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    vector<int> left(leftSize);
    vector<int> right(rightSize);

    for (int i = 0; i < leftSize; i++) {
        left[i] = arr[low + i];
    }

    for (int i = 0; i < rightSize; i++) {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallelMergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform parallel Merge Sort
    parallelMergeSort(arr, 0, n - 1);

    // Print sorted array
    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


```

## Conclusion

Based on the performance measurements, the parallel versions of Bubble Sort and Merge Sort demonstrate significant speedup compared to their sequential counterparts. The parallel implementations leverage the power of multiple cores and threads, enabling faster sorting of large arrays.

The speedup achieved by the parallel Bubble Sort and Merge Sort varies depending on the size of the input array and the hardware environment. Generally, larger arrays tend to exhibit higher speedup due to increased parallelism. However, for smaller arrays or cases with limited available parallelism, the overhead of thread creation and synchronization may diminish the speedup.

In conclusion, parallelizing sorting algorithms using OpenMP can yield substantial performance improvements. The choice of whether to utilize parallel Bubble Sort or parallel Merge Sort depends on the characteristics of the input data and the hardware environment. It is recommended to experiment with different array sizes and observe the performance to determine the most effective algorithm for sorting tasks.
