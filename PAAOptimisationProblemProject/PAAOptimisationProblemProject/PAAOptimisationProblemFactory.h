#pragma once
#include "PAAOptimisationProblem.h"
namespace PAA {
	class ProblemFactory
	{
	public:
		ProblemFactory();
		~ProblemFactory();
		virtual OptimisationProblem *create() = 0;
	};
}

