#include "Blake2b.h"

#define HASH_SIZE       64

Blake2b::Blake2b(QObject *parent) :
    IMiner(parent)
{
    _crypto = new CryptoPP::BLAKE2b();
}

void Blake2b::run()
{
    byte dig[HASH_SIZE];
    memset(dig, 0, HASH_SIZE);

    QString ss;
    quint64 ff = 0;

    for (ff = 0; ff < 150000000; ff++)
    {
        ss = QString::number(ff);
        _crypto->CalculateDigest(dig, (const byte *)ss.toUtf8().constData(), ss.length());
        appendHashCount();
        if (dig[0] + dig[1] + dig[2] + dig[3] == 0)
        {
            break;
        }
    }

    char s[HASH_SIZE * 2];
    for (int i = 0; i < HASH_SIZE; i++)
    {
        sprintf(s + i * 2, "%.2X", dig[i]);
    }
    LOG_DEBUG << s;
}
