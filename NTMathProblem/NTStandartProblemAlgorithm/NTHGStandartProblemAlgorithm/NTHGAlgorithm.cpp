#include "stdafx.h"
#include "NTHGAlgorithm.h"
#include <math.h>
#include "LinearSearch.h"

using namespace Math;

NTHGAlgorithm::NTHGAlgorithm(Math::Vector<double> *initial): NTInitialVectorAlgorithm(initial)
{
}


NTHGAlgorithm::~NTHGAlgorithm()
{
}

Vector<double> *NTHGAlgorithm::solve(NTStandartMathProblem *problem) {
	double lastF = 0;
	double f = 1e7;
	Vector<double> *solution = new Vector<double>(*initial);
	int size = solution->size();
	double *x = new double[size];
	double *direction = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*solution)[i];
	}
	double step = 1;
	NTLinearSearch linearSearch(problem);

	while (fabs(lastF - f) > 1e-3 && f > -1000) {
		bool haveValidDirection = false;
		lastF = f;
		for (int i = 0; i < size; i++) {
			direction[i] = 0;
			double f = problem->targetFunction(size, x);
			double zero = x[i];
			double plus = x[i] + step;
			double minus = x[i] - step;
			x[i] = plus;
			double fPlus = problem->targetFunction(size, x);
			x[i] = minus;
			double fMinus = problem->targetFunction(size, x);
			double value;
			x[i] = zero;

			if (fPlus < f || fMinus < f) {
				if (fPlus < fMinus) {
					direction[i] = +step;
					haveValidDirection = true;
				}
				else {
					direction[i] = -step;
					haveValidDirection = true;
				}
			}
		}

		if (!haveValidDirection) {
			step /= 2;
			lastF = -1e7;
			continue;
		}
		
		linearSearch.dsk(size, x, direction);

		f = problem->targetFunction(size, x);
	}

	for (int i = 0; i < size; i++) {
		(*solution)[i] = x[i];
	}
	delete[] direction;
	return solution;
}