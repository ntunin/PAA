#pragma once
#include "NTStandartProblems.h"
#include "NTInitialVectorAlgorithm.h"
#include "LinearSearch.h"

#ifdef NTHGSTANDARTPROBLEMALGORITHM_EXPORTS  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllexport)   
#else  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllimport)   
#endif 

class NTConjugateGradientAlgorithm: public NTGradientProblemAlgorithm, public NTInitialVectorAlgorithm
{
protected:

	double fk;
	double fkPlus1;
	double *dFk;
	double *dFkPlus1;
	int size;
	double *x;
	double *s;
	NTLinearSearch *linearSearch;
	double step = 1;
	int sign = -1;

	NTHGSTANDARTPROBLEMALGORITHM_API double getWk();
	NTHGSTANDARTPROBLEMALGORITHM_API void calculateNewDirection(int size, double *dFk, double *dFkPlus1, double *sk);
public:
	NTHGSTANDARTPROBLEMALGORITHM_API virtual Math::Vector<double> *solve(NTGradientProblem *problem);
	NTHGSTANDARTPROBLEMALGORITHM_API NTConjugateGradientAlgorithm(Math::Vector<double> *initial);
	NTHGSTANDARTPROBLEMALGORITHM_API virtual void makeStep(NTGradientProblem *problem);
	NTHGSTANDARTPROBLEMALGORITHM_API ~NTConjugateGradientAlgorithm();
};

