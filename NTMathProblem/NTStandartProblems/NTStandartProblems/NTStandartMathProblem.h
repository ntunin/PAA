#pragma once
#include "NTMath.h"
#include <string>

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
		NTSTANDARTPROBLEMS_API virtual std::string stepDescription(int size, double *v);
		NTSTANDARTPROBLEMS_API NTStandartMathProblem();
		NTSTANDARTPROBLEMS_API ~NTStandartMathProblem();
	};

}