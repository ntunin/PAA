#pragma once
#include "NTStandartProblems.h"
#include "NTInitialVectorAlgorithm.h"

#ifdef NTHGSTANDARTPROBLEMALGORITHM_EXPORTS  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllexport)   
#else  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllimport)   
#endif 

class NTConjugateGradientAlgorithm: public NTGradientProblemAlgorithm, public NTInitialVectorAlgorithm
{
public:
	Math::Vector<double> *solve(NTGradientProblem *problem);
	NTHGSTANDARTPROBLEMALGORITHM_API NTConjugateGradientAlgorithm(Math::Vector<double> *initial);
	NTHGSTANDARTPROBLEMALGORITHM_API ~NTConjugateGradientAlgorithm();
};

