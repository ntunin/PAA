#pragma once
#include "NTStandartProblems.h"
#include "NTInitialVectorAlgorithm.h"

#ifdef NTHGSTANDARTPROBLEMALGORITHM_EXPORTS  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllexport)   
#else  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllimport)   
#endif 


class NTGradientAlgorithm: public NTGradientProblemAlgorithm, public NTInitialVectorAlgorithm
{
private:
	Math::Vector<double> *initial;
public:
	Math::Vector<double> *solve(NTGradientProblem *problem);
	NTHGSTANDARTPROBLEMALGORITHM_API NTGradientAlgorithm(Math::Vector<double> *initial);
	NTHGSTANDARTPROBLEMALGORITHM_API ~NTGradientAlgorithm();
};

