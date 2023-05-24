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
