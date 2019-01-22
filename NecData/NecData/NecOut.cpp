#include "stdafx.h"
#include "NecOut.h"
#include <math.h>


#ifndef PI
#define PI 3.14159265359
#endif // !PI


NecOut::NecOut()
{
}


NecOut::~NecOut()
{
}


NecOut::Source::Source(int tag, int seg, double vRe, double vIm, double iRe, double iIm, double zRe, double zIm, double aRe, double aIm, double power) {
	this->tag = tag;
	this->seg = seg;
	this->v = Complex(vRe, vIm);
	this->i = Complex(iRe, iIm);
	this->z = Complex(zRe, zIm);
	this->a = Complex(aRe, aIm);
	this->power = power;
}

void NecOut::addSource(int tag, int seg, double vRe, double vIm, double iRe, double iIm, double zRe, double zIm, double aRe, double aIm, double power) {
	this->sources.push_back(Source(tag, seg, vRe, vIm, iRe, iIm, zRe, zIm, aRe, aIm, power));
}

std::vector<NecOut::Source> NecOut::getSources() {
	return this->sources;
}

NecOut::RadiationPattern::RadiationPattern(double theta, double phi, double verticalGain, double horisontalGain, double totalGain, double axialPolarisation, double polarisationTilt, std::string polarisationSense, double eThetaMagnitude, double eThetaPhase, double ePhiMagnitude, double ePhiPhase) {
	this->theta = theta;
	this->phi = phi;
	this->verticalGain = verticalGain;
	this->horisontalGain = horisontalGain;
	this->totalGain = totalGain;
	this->axialPolarisation = axialPolarisation;
	this->polarisationTilt = polarisationTilt;
	this->polarisationSense = polarisationSense;
	this->eThetaMagnitude = eThetaMagnitude;
	this->eThetaPhase = eThetaPhase;
	this->ePhiMagnitude = ePhiMagnitude;
	this->ePhiPhase = ePhiPhase;
}

NecOut::RadiationPattern::RadiationPattern() {

}

void NecOut::addRadiationPattern(double theta, double phi, double verticalGain, double horisontalGain, double totalGain, double axialPolarisation, double polarisationTilt, std::string polarisationSense, double eThetaMagnitude, double eThetaPhase, double ePhiMagnitude, double ePhiPhase) {
	this->radiationPatters.push_back(RadiationPattern(theta, phi, verticalGain, horisontalGain, totalGain, axialPolarisation, polarisationTilt, polarisationSense, eThetaMagnitude, eThetaPhase, ePhiMagnitude, ePhiPhase));
}

std::vector<NecOut::RadiationPattern> NecOut::getRadiationPatterns() {
	return this->radiationPatters;
}

NecOut::Source::Source() {

}

NecOut::Source::~Source() {

}

Complex NecOut::RadiationPattern::getE() {
	double re = this->eThetaMagnitude * cos(PI * this->eThetaPhase / 180);
	double im = this->eThetaMagnitude * sin(PI * this->eThetaPhase / 180);
	return Complex(re, im);
}

double  NecOut::RadiationPattern::getTheta() {
	return this->theta;
}

double  NecOut::RadiationPattern::getPhi() {
	return this->phi;
}

double  NecOut::RadiationPattern::getGain() {
	return this->totalGain;
}

double  NecOut::RadiationPattern::getMagnitude() {
	return this->eThetaMagnitude;
}

double  NecOut::RadiationPattern::getPhase() {
	return this->eThetaPhase;
}


NecOut::RadiationPattern::~RadiationPattern() {

}

Complex NecOut::Source::getI() {
	return this->i;
}

Complex NecOut::Source::getV() {
	return this->v;
}

