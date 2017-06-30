#ifndef BLAKE2B_H
#define BLAKE2B_H

#include <src/interfaces/IMiner.h>
#include <blake2.h>

#define H0      0xcbbb9d5dc1059ed8
#define H1      0x629a292a367cd507
#define H2      0x9159015a3070dd17
#define H3      0x152fecd8f70e5939
#define H4      0x67332667ffc00b31
#define H5      0x8eb44a8768581511
#define H6      0xdb0c2e0d64f98fa7
#define H7      0x47b5481dbefa4fa4


// state context
typedef struct {
    uint8_t b[128];                     // input buffer
    uint64_t h[8];                      // chained state
    uint64_t t[2];                      // total number of bytes
    size_t c;                           // pointer for b[]
    size_t outlen;                      // digest size
} blake2b_ctx;



class Blake2b : public IMiner
{
    Q_OBJECT

public:
    Blake2b(QObject *parent = 0);

    // IMiner interface
protected:
    void run();

private:
    byte *getHash(byte *buffer, quint32 length);
    byte *mix(byte Va, byte Vb, byte Vc, byte Vd, byte x, byte y);

    //CryptoPP::BLAKE2b *_crypto;
};

#endif // BLAKE2B_H
