#pragma once
#include "PAAOptimisationProblem.h"
#include "NTStandartProblems.h"
#include "NTMath.h"

#ifdef PAAOPTIMISATIONPROBLEMPROJECT_EXPORTS  
#define PAAOPTIMISATIONPROBLEMPROJECT_API __declspec(dllexport)   
#else  
#define PAAOPTIMISATIONPROBLEMPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class PenaltyOptimisationProblem : public OptimisationProblem, public NTGradientProblem
	{
	private:
		double factor;
		double degree;
		double *duBu;
	public:
		PAAOPTIMISATIONPROBLEMPROJECT_API PenaltyOptimisationProblem(Math::Matrix<Math::Complex> *A, std::vector<Math::Matrix<Math::Complex> *> *B, double factor, double degree);
		PAAOPTIMISATIONPROBLEMPROJECT_API PenaltyOptimisationProblem(Math::Matrix<double> *A, std::vector<Math::Matrix<double> *> *B, double factor, double degree);
		PAAOPTIMISATIONPROBLEMPROJECT_API ~PenaltyOptimisationProblem();
		PAAOPTIMISATIONPROBLEMPROJECT_API double targetFunction(int size, double *x);
		PAAOPTIMISATIONPROBLEMPROJECT_API void getGradient(int size, double *x, double *gradient);
		PAAOPTIMISATIONPROBLEMPROJECT_API void normalize(int size, double *x);
		PAAOPTIMISATIONPROBLEMPROJECT_API std::string stepDescription(int size, double *v);
	};
}

