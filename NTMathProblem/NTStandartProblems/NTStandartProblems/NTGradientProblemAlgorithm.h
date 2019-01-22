#pragma once
#include "NTGradientProblem.h"

#ifdef NTSTANDARTPROBLEMS_EXPORTS
#define NTSTANDARTPROBLEMS_API __declspec(dllexport) 
#else
#define NTSTANDARTPROBLEMS_API __declspec(dllimport) 
#endif

using namespace MathProblems;

class NTGradientProblemAlgorithm
{
public:
	NTSTANDARTPROBLEMS_API virtual Math::Vector<double> *solve(NTGradientProblem *problem) = 0;
	NTSTANDARTPROBLEMS_API NTGradientProblemAlgorithm();
	NTSTANDARTPROBLEMS_API ~NTGradientProblemAlgorithm();
};

