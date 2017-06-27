#ifndef STRATUMPARSER_H
#define STRATUMPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QJsonParseError>

#include <src/interfaces/ISingleton.h>
#include <src/interfaces/IJob.h>

class StratumParser : public ISingleton
{
public:
     static IJob *parseJob(QJsonObject &json);
};

#endif // STRATUMPARSER_H
