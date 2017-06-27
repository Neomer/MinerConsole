#ifndef ISINGLETON_H
#define ISINGLETON_H

class ISingleton
{
public:
    static ISingleton& instance()
    {
        static ISingleton s;
        return s;
    }

private:
    ISingleton();
    ~ISingleton();
    ISingleton(ISingleton &other) = delete;
    ISingleton& operator= (ISingleton const&) = delete;
};

#endif // ISINGLETON_H
