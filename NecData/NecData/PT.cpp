#include "stdafx.h"
#include "PT.h"
#include <sstream>
#include <string>


PT::PT(int flag) {
	this->flag = flag;
}

PT::PT(PT &pt) {
	this->flag = pt.flag;
}


PT::~PT()
{
}

std::string PT::toString() {
	std::stringstream stream;
	stream << "PT "
		<< ((NecCommand *)this)->toString(this->flag, 3);
	return stream.str();
}
