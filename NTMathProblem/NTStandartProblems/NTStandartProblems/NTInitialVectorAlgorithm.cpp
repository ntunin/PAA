#include "stdafx.h"
#include "NTInitialVectorAlgorithm.h"


NTInitialVectorAlgorithm::NTInitialVectorAlgorithm(Math::Vector<double> *initial)
{
	this->initial = new Math::Vector<double>(*initial);
}


NTInitialVectorAlgorithm::~NTInitialVectorAlgorithm()
{
	delete initial;
}
