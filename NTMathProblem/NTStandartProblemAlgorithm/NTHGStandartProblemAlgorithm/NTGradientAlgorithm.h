#pragma once
#include "NTStandartProblems.h"
#include "NTInitialVectorAlgorithm.h"
#include "LinearSearch.h"

#ifdef NTHGSTANDARTPROBLEMALGORITHM_EXPORTS  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllexport)   
#else  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllimport)   
#endif 


class NTGradientAlgorithm: public NTGradientProblemAlgorithm, public NTInitialVectorAlgorithm
{
protected:
	NTLinearSearch *linearSearch;
	double lastF;
	double f;
	int size;
	double *x;
	double *direction;
	double *xTmp;
	double step;
public:
	NTHGSTANDARTPROBLEMALGORITHM_API static int time;
	NTHGSTANDARTPROBLEMALGORITHM_API static int maxTime;
	NTHGSTANDARTPROBLEMALGORITHM_API virtual Math::Vector<double> *solve(NTGradientProblem *problem);
	NTHGSTANDARTPROBLEMALGORITHM_API virtual void makeStep(NTGradientProblem *problem);
	NTHGSTANDARTPROBLEMALGORITHM_API NTGradientAlgorithm(Math::Vector<double> *initial);
	NTHGSTANDARTPROBLEMALGORITHM_API ~NTGradientAlgorithm();
};


