#include "stdafx.h"
#include "PAAPhysicalSystem.h"

using namespace PAA;

PhysicalSystem::~PhysicalSystem()
{
}

PhysicalSystem::PhysicalSystem(int sourceCount, int iStep, int jStep, Math::Matrix<Math::Complex> *Y, Math::Complex ****beamPattern) {
	this->sourceCount = sourceCount;
	this->Y = Y;
	this->beamPattern = beamPattern;
	this->iStep = iStep;
	this->jStep = jStep;
}

int PhysicalSystem::getSourceCount() {
	return this->sourceCount;
}

Math::Matrix<Math::Complex> *PhysicalSystem::getY() {
	return this->Y;
}

Math::Complex ****PhysicalSystem::getBeamPattern() {
	return this->beamPattern;
}

int PhysicalSystem::getIStep() {
	return this->iStep;
}

int PhysicalSystem::getJStep() {
	return this->jStep;
}