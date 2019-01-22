#include "stdafx.h"
#include "NECStatementBuilder.h"
#include "NecInParser.h"
#include "WindowsCacheManager.h"
#include "Scanner.h"

using namespace std;
using namespace PAA;

NECStatementBuilder::NECStatementBuilder(string filename)
{
	this->filename = filename;
	cacheManager = new WindowsCacheManager("cache");
	in = new NecIn();
	NecInParser(filename, in);
}


NECStatementBuilder::~NECStatementBuilder()
{
	delete in;
}


ProblemStatement *NECStatementBuilder::buildStatement(double theta, double phi) {
	RP *rp = in->getRP();
	int thetaInc = rp->getThetaInc();
	int phiInc = rp->getPhiInc();
	double iDirect = theta / thetaInc;
	double jDirect = phi / phiInc;
	double sourceCount = (int)in->getEX()->size();
	fillOuts();
	fillY();
	fillA();
}


NecOut *NECStatementBuilder::buildOuts() {
	int sourceCount = (int)in->getEX()->size();
	NecOut **outs = new NecOut*[sourceCount];
	for (int i = 0; i < sourceCount; i++) {
		outs[i] = new NecOut;
	}

	bool cached = cacheManager->cached(filename);
	bool useCache = false;
	if (cached) {		
		useCache = Scanner::getSharedScanner()->readBool("Previosly solved values was found, use them?");
		if (useCache) {
			cacheManager->fill(filename, outs);
			return;
		}
	}
	OneSourceThread **threads = new OneSourceThread*[this->sourceCount];
	Shared::bundle().log()->print("Please wait while nec2 making calculations for one source enabled mod. \n");
	for (int i = 0; i < this->sourceCount; i++) {
		threads[i] = new OneSourceThread(in, this, i);
	}
	for (int i = 0; i < this->sourceCount; i++) {
		threads[i]->wait();
	}

	Shared::bundle().log()->print("\n");

}
