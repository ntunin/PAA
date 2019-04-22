#include "stdafx.h"
#include "NTConjugateGradientAlgorithm.h"
using namespace Math;

NTConjugateGradientAlgorithm::NTConjugateGradientAlgorithm(Math::Vector<double> *initial): NTInitialVectorAlgorithm(initial)
{
}


NTConjugateGradientAlgorithm::~NTConjugateGradientAlgorithm()
{
}

double NTConjugateGradientAlgorithm::getWk() {
	
	double division = 0;
	double divider = 0;

	for (int i = 0; i < size; i++) {
		division += dFkPlus1[i] * dFkPlus1[i];
		divider += dFk[i] * dFk[i];
	}
	return division / divider;
}

void NTConjugateGradientAlgorithm::calculateNewDirection(int size, double *dFk, double *dFkPlus1, double *sk) {
	
}

Math::Vector<double> *NTConjugateGradientAlgorithm::solve(NTGradientProblem *problem) {
	fk = -1e7;
	fkPlus1 = -fk;

	Vector<double> *solution = new Vector<double>(*initial);
	size = solution->size();

	x = new double[size];

	s = new double[size];

	dFk = new double[size];
	dFkPlus1 = new double[size];

	linearSearch = new NTLinearSearch(problem);
	step = 1;
	sign = -1;

	for (int i = 0; i < size; i++) {
		x[i] = (*solution)[i];
	}

	problem->getGradient(size, x, dFk);

	Math::Utils::copy(size, dFk, s);
	Math::Utils::copy(size, dFk, dFkPlus1);

	Math::Utils::normalize(size, s);
	//Math::Utils::mul(size, s, -1, s);       // (1) s0 = -dF(x0)


	while (fabs(fkPlus1 - fk) > 1e-6) {
		makeStep(problem);
		
		if (Math::Utils::abs(size, s) < 1e-6) { //(5) terminate: || s_{k} || < e
			break;
		}
	}

	for (int i = 0; i < size; i++) {
		(*solution)[i] = x[i];
	}

	delete[] x;
	delete[] s;
	delete[] dFk;
	delete[] dFkPlus1;

	delete linearSearch;

	return solution;
}

void NTConjugateGradientAlgorithm::makeStep(NTGradientProblem *problem) {
	linearSearch->dsk(size, x, s);    //(2) x_{k+1} <- linear search in sk

	fk = fkPlus1;
	fkPlus1 = problem->targetFunction(size, x); //(3) f(x_{k+1})
	problem->getGradient(size, x, dFkPlus1); // df(x_{k+1})
	double wk = getWk();
	double dFkLength = Math::Utils::abs(size, dFk);
	for (int i = 0; i < size; i++) { // (4) s_ { k + 1 } = s_{ k + 1 } +w_k * s_k
		s[i] = dFkPlus1[i] / dFkLength +wk * s[i];
	}
	//Math::Utils::normalize(size, s);
	Math::Utils::exchange(dFkPlus1, dFk);
}

