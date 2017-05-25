#ifndef CLAYMOREETHDUALMINER_H
#define CLAYMOREETHDUALMINER_H

#include <QObject>
#include "../Miner.h"

class ClaymoreEthDualMiner : public Miner
{
	Q_OBJECT
	
public:
	explicit ClaymoreEthDualMiner(QObject *parent = 0);
	
	QString getMinerName() { return "Claymore Dual Miner"; }	

};

#endif // CLAYMOREETHDUALMINER_H
