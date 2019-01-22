#pragma once
#include "NTStandartMathProblem.h"
#include "NTMath.h"


#ifdef NTHGSTANDARTPROBLEMALGORITHM_EXPORTS  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllexport)   
#else  
#define NTHGSTANDARTPROBLEMALGORITHM_API __declspec(dllimport)   
#endif 

namespace MathProblems {

	class NTLinearSearch
	{
	private:
		NTStandartMathProblem *problem;
		Math::Vector<double> *xNext;
		Math::Vector<double> **xTmp;
		int size;
		Math::Vector<double> *xa;
		Math::Vector<double> *xb;
		Math::Vector<double> *xc;
	public:
		NTHGSTANDARTPROBLEMALGORITHM_API void dsk(int size, double *x, double *direction);
		NTHGSTANDARTPROBLEMALGORITHM_API NTLinearSearch(NTStandartMathProblem *problem);
		NTHGSTANDARTPROBLEMALGORITHM_API ~NTLinearSearch();
	};
}

