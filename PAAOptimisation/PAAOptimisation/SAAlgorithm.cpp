 #include "pch.h"
#include "SAAlgorithm.h"

using namespace Math;
using namespace MathProblems;

SAAlgorithm::SAAlgorithm(Math::Vector<double> *initial, double T, double speed, double radius) : NTInitialVectorAlgorithm(initial)
{
	this->TInitial = T;
	this->coolDownSpeed = speed;
	this->radius = radius;
	this->r = RandomGenerator::getSharedGenerator();
}

void SAAlgorithm::getRandomOffset(double *x, int size, double radius) {
	for (int i = 0; i < size; i++) {
		xM[i] = x[i] + r->next() % ((int)(2 * radius * 1e3)) / 1e3 - radius;
	}
}

void SAAlgorithm::coppyValues(double *x, int size) {
	for (int i = 0; i < size; i++) {
		x[i] = xM[i];
	}
}

void SAAlgorithm::makeStep(MathProblems::NTStandartMathProblem *problem) {
	getRandomOffset(x, size, this->radius);
	double FM = problem->targetFunction(size, xM);
	double F = problem->targetFunction(size, x);
	double P = exp(-abs(FM - F) / T);
	double p = r->next() % 100 * 0.001;
	if (FM < F || p < P) {
		lastF = f;
		f = F;
		coppyValues(x, size);
	}
	if (T > 0) {
		T -= this->coolDownSpeed;
	}
}

Math::Vector<double> *SAAlgorithm::solve(MathProblems::NTStandartMathProblem *problem) {
	lastF = 0;
	f = 1e7;
	Vector<double> *solution = new Vector<double>(*initial);
	size = solution->size();
	x = new double[size];
	xTmp = new double[size];
	xM = new double[size];
	direction = new double[size];
	T = TInitial;
	for (int i = 0; i < size; i++) {
		x[i] = (*solution)[i];
	}
	step = 1;
	linearSearch = new NTLinearSearch(problem);

	while (fabs(lastF - f) > 1e-6) {
		makeStep(problem);
	}

	for (int i = 0; i < size; i++) {
		(*solution)[i] = x[i];
	}

	delete[] xM;
	delete[] xTmp;
	delete[] direction;
	delete[] x;
	delete linearSearch;

	return solution;

}

SAAlgorithm::~SAAlgorithm()
{
}
