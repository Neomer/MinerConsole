#include <QCoreApplication>
#include <src/logs/Logger.h>
#include <src/algo/Blake2b.h>

#include <cuda_runtime.h>
#if CUDART_VERSION < 5000

// CUDA-C includes
#include <cuda.h>

// This function wraps the CUDA Driver API into a template function
template <class T>
inline void getCudaAttribute(T *attribute, CUdevice_attribute device_attribute, int device)
{
    CUresult error =    cuDeviceGetAttribute(attribute, device_attribute, device);

    if (CUDA_SUCCESS != error)
    {
        fprintf(stderr, "cuSafeCallNoSync() Driver API error = %04d from file <%s>, line %i.\n",
                error, __FILE__, __LINE__);

        exit(EXIT_FAILURE);
    }
}

#endif /* CUDART_VERSION < 5000 */

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LOG_TRACE;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help") || !strcmp(argv[i], "?"))
        {
            printf("%s", "-h  display's help information\n"
                         "-d [0-3]  setup level of debug information\n"
                         "-a [algorithm]  setup algorithm of miner.\n"
                         "      Select from this options:\n"
                         "          dag - dagger-hashimoto\n"
                         "          eqi - equihash\n"
                         "          bla2 - blake (2b)\n"
                         ""
                   );
            return 0;
        }
    }

    Blake2b *bl = new Blake2b(&a);
    bl->setJob((IJob *)1);
    bl->start();

    //int deviceCount;
    //cudaGetDeviceCount(&deviceCount);

    return a.exec();
}
