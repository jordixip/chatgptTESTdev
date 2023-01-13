#include <CL/cl.hpp>

const char *kernel_source = R"(
    __kernel void square(__global float *data, int size) {
        int i = get_global_id(0);
        if (i < size) {
            data[i] = data[i] * data[i];
        }
    }
)";

int main() {
    float *data;
    int size = 100;
    posix_memalign((void**)&data, 4096, size * sizeof(float));

    // Create OpenCL context and command queue
    cl::Context context(CL_DEVICE_TYPE_GPU);
    cl::CommandQueue queue(context);

    // Create memory buffer on the device
    cl::Buffer buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, size * sizeof(float), data);

    // Compile OpenCL kernel
    cl::Program program(context, kernel_source);
    program.build();
    cl::Kernel kernel(program, "square");
    kernel.setArg(0, buffer);
    kernel.setArg(1, size);

    // Execute the kernel
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size), cl::NullRange);
    queue.finish();

    free(data);
    return 0;
}
