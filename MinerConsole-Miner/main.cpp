#include <QCoreApplication>
#include <src/logs/Logger.h>
#include <src/algo/Blake2b.h>

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

    Blake2b * bb = new Blake2b(&a);
    bb->setJob((IJob *)1);
    bb->start();

    return a.exec();
}
