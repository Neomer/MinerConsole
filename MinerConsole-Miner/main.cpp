#include <QCoreApplication>
#include <src/logs/Logger.h>
#include <src/algo/Blake2b.h>

#include <CLUtil.hpp>

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
    //bl->start();

    cl_uint p_cnt = 0, d_cnt = 0;

    cl_platform_id platforms[10];
    if (clGetPlatformIDs(10, platforms, &p_cnt) != CL_SUCCESS)
    {
        LOG_DEBUG << "OpenCL Error!";
    }
    LOG_INFO << "Total platforms:" << p_cnt;

    for (int i = 0; i < p_cnt; i++)
    {
        cl_device_id devs[10];
        if (clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 10, devs, &d_cnt) != CL_SUCCESS)
        {
            LOG_DEBUG << "OpenCL Error!";
        }
        LOG_INFO << "Found" << d_cnt << "device(s)" << "for platfom";
        for (int d = 0; d < d_cnt; d++)
        {
            char buf[1024];
            size_t b_size;
            clGetDeviceInfo(devs[d], CL_DEVICE_NAME, 1024, buf, &b_size);
            LOG_INFO << "Device:" << buf;
            cl_ulong size = 0;
            clGetDeviceInfo(devs[d], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &size, 0);
            LOG_INFO << size / 1048576 << "Mbytes";
        }
    }

    return a.exec();
}
