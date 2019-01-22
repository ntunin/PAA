#pragma once
#include "NTStandartMathProblem.h"

#ifdef NTSTANDARTPROBLEMS_EXPORTS
#define NTSTANDARTPROBLEMS_API __declspec(dllexport) 
#else
#define NTSTANDARTPROBLEMS_API __declspec(dllimport) 
#endif

using namespace MathProblems;

class NTStandartAlgorithm
{
public:
	NTSTANDARTPROBLEMS_API virtual Math::Vector<double> *solve(NTStandartMathProblem *problem) = 0;
};

