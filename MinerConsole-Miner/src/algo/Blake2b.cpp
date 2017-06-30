#include "Blake2b.h"

#define HASH_SIZE       64




int add_recursive(byte *data, int index = 0)
{
    //LOG_TRACE << index << data[index];
    if (data[index] == '9')
    {
        data[index] = '0';
        index++;
        //LOG_TRACE << index;
        return add_recursive(data, index);
    }
    else
    {
        data[index]++;
    }
    return index + 1;
}


Blake2b::Blake2b(QObject *parent) :
    IMiner(parent)
{
    //_crypto = new CryptoPP::BLAKE2b();
}

void Blake2b::run()
{
    byte dig[HASH_SIZE];
    memset(dig, 0, HASH_SIZE);

    quint64 ff = 0;
    byte buf[1000];
    int len = 0, tmp;
    memset(buf, '0', 1000);

    while (1)
    {
        int tmp = add_recursive(buf);
        if (tmp > len)
        {
            len = tmp;
            if (len >= 1000)
            {
                LOG_DEBUG << "Failed!";
                break;
            }
        }
        //_crypto->CalculateDigest(dig, buf, len);
        appendHashCount();
        if (dig[0] + dig[1] + dig[2] + dig[3] + dig[4] == 0)
        {
            break;
        }
    }

    char s[HASH_SIZE * 2];
    for (int i = 0; i < HASH_SIZE; i++)
    {
        sprintf(s + i * 2, "%.2X", dig[i]);
    }
    LOG_INFO << "Share found!" << s;
    emit hashReady();
}

byte *Blake2b::getHash(byte *buffer, quint32 length)
{
    quint64 h0 = H0 ^ 0x01014040;
    quint32 bytesCompressed = 0;
    quint32 bytesRemain = length;
    return 0;
}
