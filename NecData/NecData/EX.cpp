#include "stdafx.h"
#include "EX.h"
#include <sstream>

EX::EX(int type, int tag, int seg, int admittance, double valueRe, double valueIm) {
	this->type = type;
	this->tag = tag;
	this->seg = seg;
	this->admittance = admittance;
	this->value = Complex(valueRe, valueIm);
}

EX::EX(EX &ex) {
	this->type = ex.type;
	this->tag = ex.tag;
	this->seg = ex.seg;
	this->admittance = ex.admittance;
	this->value = Complex(ex.value.Re(), ex.value.Im());
}

int EX::getTag() {
	return tag;
}


void EX::setTag(int tag) {
	this->tag = tag;
}

EX::EX(EX &ex, Complex &source) {
	this->type = ex.type;
	this->tag = ex.tag;
	this->seg = ex.seg;
	this->admittance = ex.admittance;
	this->value = Complex(source.Re(), source.Im());
}


EX::EX(EX &ex, bool disabled) {
	this->type = ex.type;
	this->tag = ex.tag;
	this->seg = ex.seg;
	this->admittance = ex.admittance;
	if (disabled) {
		this->value = Complex(1e-9, 0);	
	} else {
		this->value = Complex(ex.value.Re(), ex.value.Im());
	}
}


EX::~EX()
{
}


std::string EX::toString() {
	std::stringstream stream;
	stream << "EX "
		<< ((NecCommand *)this)->toString(this->type, 2)
		<< ((NecCommand *)this)->toString(this->tag, 5)
		<< ((NecCommand *)this)->toString(this->seg, 3)
		<< ((NecCommand *)this)->toString(this->admittance, 4)
		<< ((NecCommand *)this)->toString(this->value.Re(), 12, true) << "  "
		<< ((NecCommand *)this)->toString(this->value.Im(), 12, true) << " ";
	return stream.str();
}

Complex &EX::getValue() {
	return this->value;
}
