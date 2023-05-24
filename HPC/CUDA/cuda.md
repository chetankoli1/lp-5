# CUDA Vector Addition and Matrix Multiplication

## Problem Statement

The objective of this project is to perform vector addition and matrix multiplication using CUDA. The program aims to leverage the parallel processing capabilities of GPUs to efficiently compute the addition of two large vectors and the multiplication of two matrices.

## Implementation and Performance Measurement

The CUDA program consists of two kernel functions: `vectorAddition` and `matrixMultiplication`.

The `vectorAddition` kernel function performs the addition of two large vectors by distributing the computation across multiple threads. Each thread calculates the sum of corresponding elements from the input vectors and stores the result in the output vector. The size of the vectors determines the number of threads and blocks required for parallel execution.

The `matrixMultiplication` kernel function performs matrix multiplication using a block-based approach. Each thread computes a single element of the resulting matrix by multiplying corresponding row and column elements from the input matrices. The size of the matrices determines the grid and block dimensions for parallel execution.

The program allocates memory on both the host (CPU) and the device (GPU) using CUDA's memory management functions. The input data is transferred from the host to the device using `cudaMemcpy`.

For vector addition, the program determines the grid and block dimensions based on the vector size and launches the `vectorAddition` kernel function with the specified dimensions.

Similarly, for matrix multiplication, the program determines the grid and block dimensions based on the matrix size and launches the `matrixMultiplication` kernel function with the specified dimensions.

After the kernel executions, the program copies the results back from the device to the host using `cudaMemcpy`. The results are then printed to the console.

```cpp
#include <iostream>
#include <cuda_runtime.h>

// Kernel function for vector addition
__global__ void vectorAddition(const int* a, const int* b, int* result, int size) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < size) {
        result[index] = a[index] + b[index];
    }
}

// Kernel function for matrix multiplication
__global__ void matrixMultiplication(const int* a, const int* b, int* result, int size) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < size && col < size) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += a[row * size + i] * b[i * size + col];
        }
        result[row * size + col] = sum;
    }
}

int main() {
    int size = 1024; // Size of the vectors and matrices

    // Allocate memory on the host (CPU)
    int* host_a = new int[size];
    int* host_b = new int[size];
    int* host_result = new int[size];

    // Initialize the vectors and matrices
    for (int i = 0; i < size; i++) {
        host_a[i] = i;
        host_b[i] = i;
    }

    // Allocate memory on the device (GPU)
    int* device_a;
    int* device_b;
    int* device_result;

    cudaMalloc((void**)&device_a, size * sizeof(int));
    cudaMalloc((void**)&device_b, size * sizeof(int));
    cudaMalloc((void**)&device_result, size * sizeof(int));

    // Copy input data from host to device
    cudaMemcpy(device_a, host_a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, host_b, size * sizeof(int), cudaMemcpyHostToDevice);

    // Vector addition
    int blockSize = 256;
    int gridSize = (size + blockSize - 1) / blockSize;

    vectorAddition<<<gridSize, blockSize>>>(device_a, device_b, device_result, size);

    // Copy result back from device to host
    cudaMemcpy(host_result, device_result, size * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result of vector addition
    std::cout << "Vector Addition Result:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << host_result[i] << " ";
    }
    std::cout << std::endl;

    // Matrix multiplication
    dim3 blockDim(16, 16);
    dim3 gridDim((size + blockDim.x - 1) / blockDim.x, (size + blockDim.y - 1) / blockDim.y);

    matrixMultiplication<<<gridDim, blockDim>>>(device_a, device_b, device_result, size);

    // Copy result back from device to host
    cudaMemcpy(host_result, device_result, size * size * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result of matrix multiplication
    std::cout << "Matrix Multiplication Result:" << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << host_result[i * size + j] << " ";
        }
        std::cout << std::endl;
    }

    // Free device memory
    cudaFree(device_a);
    cudaFree(device_b);
    cudaFree(device_result);

    // Free host memory
    delete[] host_a;
    delete[] host_b;
    delete[] host_result;

    return 0;
}

```

## Conclusion

The implementation of vector addition and matrix multiplication using CUDA demonstrates the benefits of utilizing the parallel processing capabilities of GPUs for computationally intensive tasks.

By leveraging CUDA's parallel execution model, the program efficiently distributes the computation across multiple threads and blocks, enabling faster execution times compared to sequential implementations.

The CUDA program effectively harnesses the power of parallelism provided by the GPU, allowing for high-performance computations on large datasets. The vector addition and matrix multiplication operations benefit from the ability to perform parallel computations on a massive scale, resulting in significant speedup compared to sequential CPU implementations.

It is important to note that the actual performance improvements achieved by using CUDA for vector addition and matrix multiplication may vary depending on factors such as the size of the vectors/matrices, the specific GPU architecture, and the memory access patterns. It is recommended to experiment with different input sizes and configurations to find the optimal settings for specific scenarios.

In conclusion, the CUDA implementation of vector addition and matrix multiplication showcases the capability of GPUs to accelerate computationally intensive tasks. The parallel execution model of CUDA allows for efficient utilization of GPU resources and enables substantial speedup for these operations.

## How to run the code
This CUDA program performs vector addition and matrix multiplication using CUDA C. It utilizes the parallel processing capabilities of NVIDIA GPUs to accelerate the computation.

### Usage

1. Make sure you have the CUDA Toolkit installed on your system. If not, download and install it from the NVIDIA website: [CUDA Toolkit](https://developer.nvidia.com/cuda-toolkit).

2. Save the program code in a file named `cuda_program.cu`.

3. Open a terminal or command prompt and navigate to the directory where the `cuda_program.cu` file is saved.

4. Compile the CUDA code using the following command:
    ```bash
    nvcc cuda_program.cu -o cuda_program
    ```
5. Run the executable:

    ```bash
    ./cuda_program
    ```

The program will perform vector addition and matrix multiplication using CUDA C. The results will be printed to the console.

Make sure that you have a compatible NVIDIA GPU and the CUDA Toolkit properly installed and configured for successful execution of the CUDA code.