#pragma once
#include "PAAOptimisationProblem.h"
#include "NTStandartProblems.h"
#include "NTMath.h"

namespace PAA {
	class PenaltyOptimisationProblem : public OptimisationProblem, public NTGradientProblem
	{
	private:
		double factor;
		double degree;
	public:
		PenaltyOptimisationProblem(Math::Matrix<Math::Complex> *A, std::vector<Math::Matrix<Math::Complex> *> *B, double factor, double degree);
		PenaltyOptimisationProblem(Math::Matrix<double> *A, std::vector<Math::Matrix<double> *> *B, double factor, double degree);
		~PenaltyOptimisationProblem();
		double targetFunction(int size, double *x);
		void getGradient(int size, double *x, double *gradient);
	};
}

