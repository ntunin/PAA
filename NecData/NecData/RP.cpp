#include "stdafx.h"
#include "RP.h"
#include <sstream>


RP::RP(int mode, int thetaNumber, int phiNumber, std::string XNDA, double theta0, double phi0, double thetaInc, double phiInc) {
	this->mode = mode;
	this->thetaNumber = thetaNumber;
	this->phiNumber = phiNumber;
	this->XNDA = XNDA;
	this->theta0 = theta0;
	this->phi0 = phi0;
	this->thetaInc = thetaInc;
	this->phiInc = phiInc;
}


RP::RP(RP &rp) {
	this->mode = rp.mode;
	this->thetaNumber = rp.thetaNumber;
	this->phiNumber = rp.phiNumber;
	this->XNDA = rp.XNDA;
	this->theta0 = rp.theta0;
	this->phi0 = rp.phi0;
	this->thetaInc = rp.thetaInc;
	this->phiInc = rp.phiInc;
}


RP::~RP()
{
}

std::string RP::toString() {
	std::stringstream stream;
	stream << "RP "
		<< ((NecCommand *)this)->toString(this->mode, 3)
		<< ((NecCommand *)this)->toString(this->thetaNumber, 4)
		<< ((NecCommand *)this)->toString(this->phiNumber, 5)
		<< this->XNDA
		<< ((NecCommand *)this)->toString(this->theta0, 4, false)
		<< ((NecCommand *)this)->toString(this->phi0, 4, false)
		<< ((NecCommand *)this)->toString(this->thetaInc, 4, false)
		<< ((NecCommand *)this)->toString(this->phiInc, 4, false);
	return stream.str();
}

int RP::getThetaNumber() {
	return this->thetaNumber;
}

int RP::getPhiNumber() {
	return this->phiNumber;
}

int RP::getThetaInc() {
	return (int)this->thetaInc;
}

int RP::getPhiInc() {
	return (int)this->phiInc;
}