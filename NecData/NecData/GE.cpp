#include "stdafx.h"
#include "GE.h"
#include <sstream>


GE::GE(int flag) {
	this->flag = flag;
}

GE::GE(GE &ge) {
	this->flag = ge.flag;
}


GE::~GE() {
}

std::string GE::toString() {
	std::stringstream stream;
	stream << "GE"
		<< ((NecCommand *)this)->toString(this->flag, 3);
	return stream.str();
}