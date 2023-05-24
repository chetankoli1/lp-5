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
