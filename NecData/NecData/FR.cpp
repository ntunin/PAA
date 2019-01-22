#include "stdafx.h"
#include "FR.h"
#include <string>
#include <sstream>


FR::FR(int steppingType, int stepsNumber, double frequency) {
	this->steppingType = steppingType;
	this->stepsNumber = stepsNumber;
	this->frequency = frequency;
}


FR::FR(FR &fr) {
	this->steppingType = fr.steppingType;
	this->stepsNumber = fr.stepsNumber;
	this->frequency = fr.frequency;
}


FR::~FR()
{
}

std::string FR::toString() {
	std::stringstream stream;
	stream << "FR "
		<< ((NecCommand *)this)->toString(this->steppingType, 3)
		<< ((NecCommand *)this)->toString(this->stepsNumber, 3) << " 0  0  "
		<< ((NecCommand *)this)->toString(this->frequency, 4, false) << " ";
	return stream.str();
}

