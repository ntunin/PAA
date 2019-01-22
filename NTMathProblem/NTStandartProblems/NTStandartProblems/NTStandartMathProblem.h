#pragma once
#include "NTMath.h"

#ifdef NTSTANDARTPROBLEMS_EXPORTS  
#define NTSTANDARTPROBLEMS_API __declspec(dllexport)   
#else  
#define NTSTANDARTPROBLEMS_API __declspec(dllimport)   
#endif 


namespace MathProblems {

	class NTStandartMathProblem
	{
	public:
		int size;
		NTSTANDARTPROBLEMS_API virtual double targetFunction(int size, double *v) = 0;
		NTSTANDARTPROBLEMS_API NTStandartMathProblem();
		NTSTANDARTPROBLEMS_API ~NTStandartMathProblem();
	};

}