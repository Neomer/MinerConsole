#ifndef BLAKE2B_H
#define BLAKE2B_H

#include <src/interfaces/IMiner.h>
#include <blake2.h>

class Blake2b : public IMiner
{
    Q_OBJECT

public:
    Blake2b(QObject *parent = 0);

    // IMiner interface
protected:
    void run();

private:
    CryptoPP::BLAKE2b *_crypto;
};

#endif // BLAKE2B_H
