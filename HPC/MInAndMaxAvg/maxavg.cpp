#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int parallelMax(const vector<int>& arr) {
    int maxVal = arr[0];
    int n = arr.size();

    #pragma omp parallel for reduction(max : maxVal)
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    return maxVal;
}

double parallelAverage(const vector<int>& arr) {
    double sum = 0.0;
    int n = arr.size();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

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

    // Perform parallel Max operation
    int maxVal = parallelMax(arr);
    cout << "Max value: " << maxVal << endl;

    // Perform parallel Average operation
    double avg = parallelAverage(arr);
    cout << "Average value: " << avg << endl;

    return 0;
}
