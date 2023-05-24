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
