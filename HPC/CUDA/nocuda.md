# Vector Addition in C++
```cpp
#include <iostream>
#include <vector>

// Function for vector addition
std::vector<int> vectorAdd(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> c(a.size());
    for (int i = 0; i < a.size(); i++) {
        c[i] = a[i] + b[i];
    }
    return c;
}

int main() {
    int n = 1000000; // Size of the vectors

    // Initialize the vectors
    std::vector<int> a(n);
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition
    std::vector<int> c = vectorAdd(a, b);

    // Print the result
    for (int i = 0; i < n; i++) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

# Matrix Multiplication in C++

```cpp
#include <iostream>
#include <vector>

#define N 1024  // Matrix size

// Function for matrix multiplication
std::vector<int> matrixMul(const std::vector<int>& a, const std::vector<int>& b, int n) {
    std::vector<int> c(n * n);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += a[row * n + i] * b[i * n + col];
            }
            c[row * n + col] = sum;
        }
    }
    return c;
}

int main() {
    // Initialize the matrices
    std::vector<int> a(N * N);
    std::vector<int> b(N * N);
    for (int i = 0; i < N * N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform matrix multiplication
    std::vector<int> c = matrixMul(a, b, N);

    // Print the result
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << c[i * N + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}


```
