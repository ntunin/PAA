#include "stdafx.h"
#include "GN.h"
#include <sstream>
#include <string>


GN::GN(int groundType, int radialWiresNumber, double dielectricConstant, double conductivity) {
	this->groundType = groundType;
	this->radialWiresNumber = radialWiresNumber;
	this->dielectricConstant = dielectricConstant;
	this->conductivity = conductivity;
}

int GN::getType() {
	return this->groundType;
}

GN::GN(GN &gn) {
	this->groundType = gn.groundType;
	this->radialWiresNumber = gn.radialWiresNumber;
	this->dielectricConstant = gn.dielectricConstant;
	this->conductivity = gn.conductivity;
}


GN::~GN()
{
}

std::string GN::toString() {
	std::stringstream stream;
	std::string str1 = ((NecCommand *)this)->toString(this->dielectricConstant, 5, false);
	if (this->groundType >= 0) {
		stream << "GN "
			<< ((NecCommand *)this)->toString(this->groundType, 3)
			<< ((NecCommand *)this)->toString(this->radialWiresNumber, 3) << " 0  0 "
			<< ((NecCommand *)this)->toString(this->dielectricConstant, 5, false) << "  "
			<< ((NecCommand *)this)->toString(this->conductivity, 5, false) << " ";
	} else {
		stream << "GN "
			<< ((NecCommand *)this)->toString(this->groundType, 3) << " ";
	}
	
	return stream.str();
}

