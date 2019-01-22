#pragma once
#include "NTMath.h"

#ifdef NTSTANDARTPROBLEMS_EXPORTS
#define NTSTANDARTPROBLEMS_API __declspec(dllexport) 
#else
#define NTSTANDARTPROBLEMS_API __declspec(dllimport) 
#endif

class NTInitialVectorAlgorithm
{
protected:
	Math::Vector<double> *initial;
public:
	NTSTANDARTPROBLEMS_API NTInitialVectorAlgorithm(Math::Vector<double> *initial);
	NTSTANDARTPROBLEMS_API ~NTInitialVectorAlgorithm();
};

