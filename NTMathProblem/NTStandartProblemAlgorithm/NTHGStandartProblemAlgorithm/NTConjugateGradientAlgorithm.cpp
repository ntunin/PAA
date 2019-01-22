#include "stdafx.h"
#include "NTConjugateGradientAlgorithm.h"
#include "LinearSearch.h"
using namespace Math;

NTConjugateGradientAlgorithm::NTConjugateGradientAlgorithm(Math::Vector<double> *initial): NTInitialVectorAlgorithm(initial)
{
}


NTConjugateGradientAlgorithm::~NTConjugateGradientAlgorithm()
{
}

Math::Vector<double> *NTConjugateGradientAlgorithm::solve(NTGradientProblem *problem) {
	double lastF = 1e7;
	double f = -1e7;

	Vector<double> *solution = new Vector<double>(*initial);
	int size = solution->size();
	double *x = new double[size];
	double *xTmp = new double[size];
	double *gradient = new double[size];
	double *gradient_1 = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*solution)[i];
		xTmp[i] = (*solution)[i];
	}
	NTLinearSearch linearSearch(problem);
	double step = 1;
	int sign = -1;

	while (fabs(lastF - f) > 1e-12 && step > 0) {
		bool haveValidDirection = false;
		lastF = f;
		double absDfk;
		double absDfk_1;
		problem->getGradient(size, xTmp, gradient_1);
		absDfk_1 = Math::Utils::abs(size, gradient_1);
		Math::Utils::normalize(size, gradient_1);
		Math::Utils::mul(size, gradient_1, -1, gradient_1);
		linearSearch.dsk(size, xTmp, gradient_1);

		for (int k = 1; k < size; k++) {
			f = problem->targetFunction(size, x);
			problem->getGradient(size, xTmp, gradient);
			absDfk = Utils::abs(size, gradient);
			Math::Utils::mul(size, gradient, -1, gradient);
			Math::Utils::normalize(size, gradient);
			double wk = pow(absDfk, 2) / pow(absDfk_1, 2);
			absDfk_1 = absDfk;
			for (int i = 0; i < size; i++) {
				gradient_1[i] = gradient[i] + wk * gradient_1[i];
			}
			linearSearch.dsk(size, xTmp, gradient_1);

			f = problem->targetFunction(size, x);
			double fNew = problem->targetFunction(size, xTmp);
			if (fNew > f) {
				for (int i = 0; i < size; i++) {
					xTmp[i] = x[i];
				}
				continue;
			}
			for (int i = 0; i < size; i++) {
				x[i] = xTmp[i];
			}
		}

	}

	for (int i = 0; i < size; i++) {
		(*solution)[i] = x[i];
	}
	delete[] x;
	delete[] xTmp;
	delete[] gradient;
	delete[] gradient_1;

	return solution;
}

