#include "stdafx.h"
#include "NTGradientAlgorithm.h"
#include <math.h>
#include "LinearSearch.h"

using namespace Math;


NTGradientAlgorithm::NTGradientAlgorithm(Math::Vector<double> *initial): NTInitialVectorAlgorithm(initial)
{
}


NTGradientAlgorithm::~NTGradientAlgorithm()
{
}

Math::Vector<double> *NTGradientAlgorithm::solve(NTGradientProblem *problem) {
	double lastF = 0;
	double f = 1e7;
	Vector<double> *solution = new Vector<double>(*initial);
	int size = solution->size();
	double *x = new double[size];
	double *xTmp = new double[size];
	double *direction = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*solution)[i];
	}
	double step = 1;
	NTLinearSearch linearSearch(problem);

	while (fabs(lastF - f) > 1e-9) {
		bool haveValidDirection = false;
		lastF = f;
		f = problem->targetFunction(size, x);
		problem->getGradient(size, x, direction);
		Utils::normalize(size, direction);

		for (int i = 0; i < size; i++) {
			xTmp[i] = x[i] + step * direction[i];
		}
		double fPlus = problem->targetFunction(size, xTmp);

		if (fPlus < f) {
			haveValidDirection = true;
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
	delete[] x;

	return solution;
		
}