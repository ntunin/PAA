#pragma once
#include "NTMath.h"
#include "NTStandartMathProblem.h"
#include <vector>

#ifdef PAAOPTIMISATIONPROBLEMPROJECT_EXPORTS  
#define PAAOPTIMISATIONPROBLEMPROJECT_API __declspec(dllexport)   
#else  
#define PAAOPTIMISATIONPROBLEMPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class OptimisationProblem
	{
	private:
		Math::Matrix<double> *fillA(Math::Matrix<Math::Complex> *A);
		std::vector<Math::Matrix<double>*> *fillB(std::vector<Math::Matrix<Math::Complex> *> *B);
		Math::Matrix<double> *fillA(Math::Matrix<double> *A);
		std::vector<Math::Matrix<double>*> *fillB(std::vector<Math::Matrix<double>*> *B);
		double *lastCheckedSolution;
		std::vector<double> *uBus;
		double *v;
		double *Au;
		double *Bu;
		void gradientA(int size, double x, double *result);
		void gradientB(int size, double x, double *result);
	protected:
		Math::Matrix<double> *A;
		std::vector<Math::Matrix<double> *> *B;
		int sourcesCount;
	public:
		PAAOPTIMISATIONPROBLEMPROJECT_API OptimisationProblem(Math::Matrix<Math::Complex> *A, std::vector<Math::Matrix<Math::Complex> *> *B);
		PAAOPTIMISATIONPROBLEMPROJECT_API OptimisationProblem(Math::Matrix<double> *A, std::vector<Math::Matrix<double> *> *B);
		PAAOPTIMISATIONPROBLEMPROJECT_API std::vector<double> *calculate_uBu(int size, double *v);
		PAAOPTIMISATIONPROBLEMPROJECT_API double calculate_uAu(int size, double *v);
		PAAOPTIMISATIONPROBLEMPROJECT_API ~OptimisationProblem();

	};
}

