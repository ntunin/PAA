#pragma once
#include "NTStandartMathProblem.h"
#include "NTMath.h"

#ifdef NTSTANDARTPROBLEMS_EXPORTS  
#define NTSTANDARTPROBLEMS_API __declspec(dllexport)   
#else  
#define NTSTANDARTPROBLEMS_API __declspec(dllimport)   
#endif 

namespace MathProblems {

	class NTGradientProblem : public NTStandartMathProblem
	{
	public:
		NTSTANDARTPROBLEMS_API virtual void getGradient(int size, double *x, double *gradient) = 0;
		NTSTANDARTPROBLEMS_API NTGradientProblem();
		NTSTANDARTPROBLEMS_API ~NTGradientProblem();
	};

}
