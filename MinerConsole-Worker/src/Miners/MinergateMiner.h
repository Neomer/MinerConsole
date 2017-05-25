#ifndef MINERGATEMINER_H
#define MINERGATEMINER_H

#include <QObject>
#include "../Miner.h"

class MinergateMiner : public Miner
{
	Q_OBJECT
public:
	explicit MinergateMiner(QObject *parent = 0);
	
	QString getMinerName() { return "Minergate console miner"; }
};

#endif // MINERGATEMINER_H
