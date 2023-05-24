# Parallel Min, Max, Sum, and Average Operations

## Problem Statement

The goal of this project is to implement the Min, Max, Sum, and Average operations using parallel reduction with OpenMP. The program calculates the minimum value, maximum value, sum, and average of a given array by distributing the computation across multiple threads and leveraging the parallel computing capabilities.

## Implementation and Performance Measurement

The program utilizes parallel reduction to efficiently perform the Min, Max, Sum, and Average operations on the input array.

For the Min operation, the program uses the `reduction(min: variable)` clause in the `#pragma omp parallel for` directive to distribute the computation of finding the minimum value among multiple threads. Each thread independently calculates the minimum value of its assigned portion of the array, and the reduction operation combines the local minimum values to obtain the final result.

Similarly, for the Max operation, the program employs the `reduction(max: variable)` clause in the `#pragma omp parallel for` directive. Each thread computes the maximum value of its assigned portion of the array, and the reduction operation combines the local maximum values to calculate the overall maximum value.

For the Sum operation, the program utilizes the `reduction(+: variable)` clause in the `#pragma omp parallel for` directive. Each thread calculates the sum of its assigned portion of the array, and the reduction operation accumulates the local sums to compute the total sum.

Finally, for the Average operation, the program leverages the parallel Sum operation to compute the sum of the array elements. The average is then obtained by dividing the total sum by the number of elements in the array.

The use of parallel reduction allows the program to take advantage of parallel computing capabilities, distributing the workload across multiple threads and reducing the overall execution time.

## Code
```cpp
#include <iostream>
#include <vector>
#include <limits>
#include <omp.h>

using namespace std;

int parallelMin(const vector<int>& arr) {
    int minVal = numeric_limits<int>::max();
    int n = arr.size();

    #pragma omp parallel for reduction(min : minVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    return minVal;
}

int parallelMax(const vector<int>& arr) {
    int maxVal = numeric_limits<int>::min();
    int n = arr.size();

    #pragma omp parallel for reduction(max : maxVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    return maxVal;
}

int parallelSum(const vector<int>& arr) {
    int sum = 0;
    int n = arr.size();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}

double parallelAverage(const vector<int>& arr) {
    double sum = parallelSum(arr);
    int n = arr.size();

    return sum / n;
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

    // Perform parallel Min operation
    int minVal = parallelMin(arr);
    cout << "Min value: " << minVal << endl;

    // Perform parallel Max operation
    int maxVal = parallelMax(arr);
    cout << "Max value: " << maxVal << endl;

    // Perform parallel Sum operation
    int sum = parallelSum(arr);
    cout << "Sum: " << sum << endl;

    // Perform parallel Average operation
    double avg = parallelAverage(arr);
    cout << "Average value: " << avg << endl;

    return 0;
}

```

## Conclusion

The implementation of the Min, Max, Sum, and Average operations using parallel reduction with OpenMP demonstrates improved performance compared to their sequential counterparts. By leveraging parallel computing capabilities, the program effectively distributes the computation across multiple threads, resulting in faster execution times.

Parallel reduction offers an efficient approach to compute the minimum value, maximum value, sum, and average of an array in parallel. It allows for better utilization of the available computational resources, particularly in scenarios with large arrays or high-dimensional data. The reduction operation effectively combines the results obtained by individual threads, ensuring accurate and efficient calculation of the final result.

It is worth noting that the actual speedup achieved by parallel reduction may vary depending on factors such as the size of the array, the number of available threads, and the hardware environment. It is recommended to experiment with different array sizes and observe the performance to determine the optimal approach for specific scenarios.

In conclusion, the implementation of Min, Max, Sum, and Average operations using parallel reduction demonstrates the benefits of parallel computing for computational tasks. It showcases the efficiency and scalability of OpenMP in utilizing multiple threads to achieve improved performance.

