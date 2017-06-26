#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QIcon>
#include <QApplication>

class Coin : public QObject
{
    Q_OBJECT

public:
    explicit Coin(QJsonObject object, QObject *parent = nullptr);

    void setShortName(QString value) { _shortname = value; }
    QString getShortName() { return _shortname; }

    void setName(QString value) { _name = value; }
    QString getName() { return _name; }

    void setIcon(QIcon value) { _icon = value; }
    QIcon getIcon() { return _icon; }

private:
    QString _shortname, _name;
    QIcon _icon;
};

#endif // COIN_H
