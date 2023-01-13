#include <cuda_runtime.h>

__global__ void kernel(float *data, int size) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < size) {
        data[i] = data[i] * data[i];
    }
}

int main() {
    float *data;
    int size = 100;
    cudaMalloc(&data, size * sizeof(float));

    kernel<<<1, size>>>(data, size);

    cudaDeviceSynchronize();
    cudaFree(data);

    return 0;
}
