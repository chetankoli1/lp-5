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
