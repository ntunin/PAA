#pragma once
#include "NTStandartProblems.h"
#include "NTInitialVectorAlgorithm.h"

#ifdef NTHGSTANDARTPROBLEMALGORITHM_EXPORTS  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllexport)   
#else  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllimport)   
#endif 

class NTHGAlgorithm: public NTStandartAlgorithm, public NTInitialVectorAlgorithm
{
public:
	NTHGSTANDARTPROBLEMALGORITHM_API Math::Vector<double> *solve(NTStandartMathProblem *problem);
	NTHGSTANDARTPROBLEMALGORITHM_API NTHGAlgorithm(Math::Vector<double> *initial);
	NTHGSTANDARTPROBLEMALGORITHM_API ~NTHGAlgorithm();
};

