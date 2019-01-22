#include "stdafx.h"
#include "NECPhysicalSystemBuilder.h"
#include "NecInParser.h"
#include "WindowsCacheManager.h"
#include "Scanner.h"
#include "NecRunner.h"
#include "NecIn.h"
#include "Log.h"

#include <vector>

using namespace std;
using namespace PAA;
using namespace Math;

NECPhysicalSystemBuilder::NECPhysicalSystemBuilder(string filename)
{
	this->filename = filename;
	cacheManager = new WindowsCacheManager("cache", filename);
	in = new NecIn();
	NecInParser(filename, in);
}


NECPhysicalSystemBuilder::~NECPhysicalSystemBuilder()
{
	delete in;
}


PhysicalSystem *NECPhysicalSystemBuilder::buildSystem(bool useCache) {
	int sourceCount = in->getEX()->size();
	NecOut **outs = buildOuts(useCache);
	Matrix<Complex> *Y = buildY(sourceCount, outs);
	Complex ****beamPattern = buildBeamPattern(sourceCount, in, outs);
	RP *rp = in->getRP();
	int phiStep = rp->getPhiInc();
	int thetaStep = rp->getThetaInc();
	PhysicalSystem *system = new PhysicalSystem(sourceCount, thetaStep, phiStep, Y, beamPattern);
	return system;
}


NecOut **NECPhysicalSystemBuilder::buildOuts(bool useCache) {
	int sourceCount = (int)in->getEX()->size();
	NecOut **outs = new NecOut*[sourceCount];
	for (int i = 0; i < sourceCount; i++) {
		outs[i] = new NecOut;
	}

	bool cached = cacheManager->cached(filename);
	if (cached) {		
		if (useCache) {
			cacheManager->fill(filename, outs);
			return outs;
		}
	}
	NecRunner** runners = new NecRunner*[sourceCount];
	Log::getSharedLog()->print("Please wait while nec2 making calculations for one source enabled mod. \n");
	for (int i = 0; i < sourceCount; i++) {
		runners[i] = new NecRunner(in);
		runners[i]->runNEC(cacheManager, i, outs);
	}
	for (int i = 0; i < sourceCount; i++) {
		runners[i]->wait();
		delete runners[i];
	}
	delete[] runners;

	Log::getSharedLog()->print("\n");
	return outs;
}


Matrix<Complex> *NECPhysicalSystemBuilder::buildY(int sourceCount, NecOut **outs) {
	Matrix<Complex> *Y = new Matrix<Complex>(sourceCount);
	for (int sourceNumber = 0; sourceNumber < sourceCount; sourceNumber++) {
		vector<NecOut::Source> sources = outs[sourceNumber]->getSources();
		for (int i = 0; i < sourceCount; i++) {
			if (abs(sources[i].getV().Re()) > 1e-9) {
				for (int j = 0; j < sourceCount; j++) {
					Complex c = sources[j].getI() / sources[i].getV();
					(*Y)[i][j] = c;
				}
				break;
			}
		}
	}

	return Y;
}


Complex ****NECPhysicalSystemBuilder::buildBeamPattern(int sourceCount, NecIn *in, NecOut **outs) {
	RP *rp = in->getRP();
	int thetaNumber = rp->getThetaNumber();
	int phiNumber = rp->getPhiNumber();
	Complex ****A = new Complex***[sourceCount];
	for (int i = 0; i < sourceCount; i++) {
		A[i] = new Complex**[sourceCount];
		vector<NecOut::RadiationPattern> rpI = outs[i]->getRadiationPatterns();
		for (int j = 0; j < sourceCount; j++) {
			A[i][j] = new Complex*[thetaNumber];
			vector<NecOut::RadiationPattern> rpJ = outs[j]->getRadiationPatterns();
			for (int k = 0; k < thetaNumber; k++) {
				A[i][j][k] = new Complex[phiNumber];
				for (int l = 0; l < phiNumber; l++) {
					int index = l * thetaNumber + k;
					Complex e3 = rpI[index].getE();
					Complex e2 = rpJ[index].getE();
					double re = e3.Re()* e2.Re() + e3.Im() * e2.Im();
					double im = -(e3.Im()*e2.Re()) + (e3.Re() * e2.Im());

					if ((i == 0) && (k == 1) && (l == 1)) {
						double r1 = (e3.Im()*e2.Re());
						double r2 = (e3.Re() * e2.Im());
						int a = 0;
					}
					A[i][j][k][l] = Complex(re, im);
				}
			}
		}
	}
	return A;
}
