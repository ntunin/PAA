#pragma once
#include "NTStandartProblems.h"

#ifdef NTHGSTANDARTPROBLEMALGORITHM_EXPORTS  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllexport)   
#else  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllimport)   
#endif 


class LinearSearchAlgorithm : public NTGradientProblemAlgorithm
{
protected:
	NTHGSTANDARTPROBLEMALGORITHM_API virtual void solve_gradient_problem(NTGradientProblem *problem) = 0;
public:
	NTHGSTANDARTPROBLEMALGORITHM_API LinearSearchAlgorithm();
	NTHGSTANDARTPROBLEMALGORITHM_API ~LinearSearchAlgorithm();
};



