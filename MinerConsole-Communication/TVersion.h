#ifndef TVERSION_H
#define TVERSION_H

#include <QObject>

class TVersion : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int Major READ Major WRITE setMajor)
    Q_PROPERTY(int Minor READ Minor WRITE setMinor)

    int m_Major;
    int m_Minor;

public:
    explicit TVersion();
    explicit TVersion(QString value);
    TVersion(const TVersion &other);

    int Major() const;
    int Minor() const;

    bool operator !=(const TVersion &other);
    bool operator ==(const TVersion &other);
    bool operator <(const TVersion &other);
    bool operator <=(const TVersion &other);
    bool operator >(const TVersion &other);
    bool operator >=(const TVersion &other);

    void operator =(const TVersion &other);

    operator QString();
    operator const char*() ;

public slots:
    void setMajor(int Major);
    void setMinor(int Minor);
};

#endif // TVERSION_H
