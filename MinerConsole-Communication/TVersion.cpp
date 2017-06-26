#include "TVersion.h"
#include "Err.h"

TVersion::TVersion()
{
    LOG_TRACE;

    setMajor(0);
    setMinor(0);
}

TVersion::TVersion(QString value)
{
    LOG_TRACE << value;

    QStringList sl = value.split('.');
    if (sl.isEmpty())
    {
        qDebug() << E_WRONG_FORMAT << value;
        throw std::runtime_error(E_WRONG_FORMAT.toStdString());
    }


}

TVersion::TVersion(const TVersion &other)
{
    setMajor(other.Major());
    setMinor(other.Minor());
}

int TVersion::Major() const
{
    return m_Major;
}

int TVersion::Minor() const
{
    return m_Minor;
}

bool TVersion::operator !=(const TVersion &other)
{
    return (this->Major() != other.Major()) && (this->Minor() != other.Minor());
}

bool TVersion::operator ==(const TVersion &other)
{
    return (this->Major() == other.Major()) && (this->Minor() == other.Minor());
}

bool TVersion::operator <(const TVersion &other)
{
    return (this->Major() < other.Major()) || ((this->Major() == other.Major()) && (this->Minor() < other.Minor()));
}

bool TVersion::operator <=(const TVersion &other)
{
    return (this->Major() <= other.Major()) || ((this->Major() == other.Major()) && (this->Minor() <= other.Minor()));
}

bool TVersion::operator >(const TVersion &other)
{
    return (this->Major() > other.Major()) || ((this->Major() == other.Major()) && (this->Minor() > other.Minor()));
}

bool TVersion::operator >=(const TVersion &other)
{
    return (this->Major() >= other.Major()) || ((this->Major() == other.Major()) && (this->Minor() >= other.Minor()));
}

void TVersion::operator =(const TVersion &other)
{
    setMajor(other.Major());
    setMinor(other.Minor());
}

TVersion::operator const char *()
{
    return QString::number( this->Major() ).append(".").append(QString::number( this->Minor() )).toUtf8().constData();
}

TVersion::operator QString()
{
    return QString::number( this->Major() ).append(".").append(QString::number( this->Minor() ));
}

void TVersion::setMajor(int Major)
{
    m_Major = Major;
}

void TVersion::setMinor(int Minor)
{
    m_Minor = Minor;
}
