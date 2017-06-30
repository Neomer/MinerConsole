#include <iostream>
#include <stdio.h>

using namespace std;

#include <CL/cl.h>
#define MAT_SIZE 1024

void total_info()
{
    cl_uint p_cnt = 0, d_cnt = 0;

    cl_platform_id platforms[10];
    if (clGetPlatformIDs(10, platforms, &p_cnt) != CL_SUCCESS)
    {
        cout << "OpenCL Error!" << endl;
    }
    cout << "Total platforms:" << p_cnt << endl;

    for (int i = 0; i < p_cnt; i++)
    {
        cl_device_id devs[10];
        if (clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 10, devs, &d_cnt) != CL_SUCCESS)
        {
            cout << "OpenCL Error!" << endl;
        }
        cout << "Found" << d_cnt << "device(s)" << "for platfom" << endl;
        for (int d = 0; d < d_cnt; d++)
        {
            char buf[1024];
            size_t b_size;
            clGetDeviceInfo(devs[d], CL_DEVICE_NAME, 1024, buf, &b_size);
            cout << "Device:" << buf << endl;
            cl_ulong size = 0;
            clGetDeviceInfo(devs[d], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &size, 0);
            cout << size << "bytes" << endl;
        }
    }
}

int main()
{
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem mobj_A = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int err;

    char device_name[1024];
    cl_ulong device_memory = 0;
    cl_uint device_comp_units = 0;
    cl_uint device_freq = 0;

    char source_buffer[10240];
    memset(source_buffer, 0, 10240);


    float mat_a[ MAT_SIZE ];
    for ( cl_int i = 0; i < MAT_SIZE; i++ ) {
        mat_a[i] = i;
    }

    cout << "Step 1: Get platfrom ID .. ";
    if (clGetPlatformIDs(1, &platform_id, 0) != CL_SUCCESS)
    {
        cout << "clGetPlatformIDs FAILED!" << endl;
        return -1;
    }
    cout << "SUCCESS" << endl;

    cout << "Step 2: Get Device ID .. ";
    if (clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, 0) != CL_SUCCESS)
    {
        cout << "clGetDeviceIDs FAILED!" << endl;
        return -1;
    }
    cout << "SUCCESS" << endl;
    clGetDeviceInfo(device_id, CL_DEVICE_NAME, 1024, device_name, 0);
    clGetDeviceInfo(device_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &device_memory, 0);
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &device_comp_units, 0);
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &device_freq, 0);
    cout << "Device info: " << endl
         << "\tDevice: " << device_name << endl
         << "\tMemory: " << device_memory / 1048576 << " Mbyte(s)" << endl
         << "\tCompute units: " << device_comp_units << endl
         << "\tFrequency: " << device_freq << " MHz" << endl;

    cout << "Step 3: Create OpenCL Context .. ";
    context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &err);
    if (err != CL_SUCCESS)
    {
        cout << "clCreateContext FAILED!" << endl;
        return -1;
    }
    cout << "SUCCESS" << endl;

    cout << "Step 4: Create Command Queue .. ";
    command_queue = clCreateCommandQueue( context, device_id, 0, &err );
    if (err != CL_SUCCESS)
    {
        cout << "clCreateCommandQueue FAILED!" << endl;
        goto releaseContext;
    }
    cout << "SUCCESS" << endl;

    cout << "Step 5: Create memory buffer .. ";
    mobj_A = clCreateBuffer( context, CL_MEM_READ_WRITE, MAT_SIZE * sizeof(float), NULL, &err );
    if (err != CL_SUCCESS)
    {
        cout << "clCreateBuffer FAILED!" << endl;
        goto releaseCommandQueue;
    }
    cout << "SUCCESS" << endl;

    cout << "Step 6: Tranfer the data to memory buffer .. ";
    if (clEnqueueWriteBuffer( command_queue, mobj_A, CL_TRUE, 0, MAT_SIZE * sizeof(float), mat_a, 0, NULL, NULL ) != CL_SUCCESS)
    {
        cout << "clCreateBuffer FAILED!" << endl;
        goto releaseMemory;
    }
    cout << "SUCCESS" << endl;

    cout << "Step 7: Read kernel file .. ";
    FILE *file = fopen("SomeFunc.c", "r");
    if (!file)
    {
        cout << "fopen FAILED!" << endl;
        goto releaseMemory;
    }

    size_t filesize = fread(source_buffer, 1, 10240, file);
    source_buffer[filesize] = 0;
    cout << "SUCCESS" << endl;
    cout << "\tSource file size: " << filesize << " bytes" << endl;

    cout << "Step 8: Create Kernel program from source .. ";
    try {
    program = clCreateProgramWithSource( context, 1, (const char **)&source_buffer, 0, &err );
    if (err != CL_SUCCESS)
    {
        cout << "clCreateProgramWithSource FAILED!" << endl;
        goto releaseMemory;
    }
    cout << "SUCCESS" << endl;
    } catch (std::exception &e)
    {
        cout << e.what();
    }


releaseProgram:
    cout << "Step : Releasing program .. ";
    clReleaseProgram(program);
    cout << "SUCCESS" << endl;

releaseMemory:
    cout << "Step : Releasing memory buffer .. ";
    clReleaseMemObject(mobj_A);
    cout << "SUCCESS" << endl;

releaseCommandQueue:
    cout << "Step : Releasing Command Queue .. ";
    clReleaseCommandQueue(command_queue);
    cout << "SUCCESS" << endl;

releaseContext:
    cout << "Step : Releasing OpenCL context .. ";
    clReleaseContext(context);
    cout << "SUCCESS" << endl;

    return 0;
}
