#pragma once
#include "PAAOptimisationProblem.h"

#ifdef PAAOPTIMISATIONPROBLEMPROJECT_EXPORTS  
#define PAAOPTIMISATIONPROBLEMPROJECT_API __declspec(dllexport)   
#else  
#define PAAOPTIMISATIONPROBLEMPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class ProblemFactory
	{
	public:
		PAAOPTIMISATIONPROBLEMPROJECT_API ProblemFactory();
		PAAOPTIMISATIONPROBLEMPROJECT_API ~ProblemFactory();
		PAAOPTIMISATIONPROBLEMPROJECT_API virtual OptimisationProblem *create() = 0;
	};
}

