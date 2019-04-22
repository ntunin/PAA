#include "pch.h"
#include "NTGSAAlgorithm.h"


NTGSAAlgorithm::NTGSAAlgorithm(Math::Vector<double> *initial, double T, double speed, double radius): NTGradientAlgorithm(initial)
{
	this->TInitial = T;
	this->coolDownSpeed = speed;
	this->radius = radius;
}

void NTGSAAlgorithm::getRandomOffset(double *x, int size, double radius) {
	for (int i = 0; i < size; i++) {
		xM[i] = x[i] + r->next() % ((int)(2 * radius * 1e3)) / 1e3 - radius;
	}
}

void NTGSAAlgorithm::coppyValues(double *x, int size) {
	for (int i = 0; i < size; i++) {
		x[i] = xM[i];
	}
}

void NTGSAAlgorithm::makeStep(NTGradientProblem *problem) {
	if (T > 0) {
		getRandomOffset(x, size, this->radius);
		double FM = problem->targetFunction(size, xM);
		double F = problem->targetFunction(size, x);
		double P = exp(-abs(FM - F) / T);
		double p = r->next() % 100 * 0.01;
		if (FM < F || p < P) {
			coppyValues(x, size);
		}
		T -= this->coolDownSpeed;
	}
	NTGradientAlgorithm::makeStep(problem);
}

Math::Vector<double> *NTGSAAlgorithm::solve(NTGradientProblem *problem) {
	xM = new double[problem->size];
	T = TInitial;
	r = RandomGenerator::getSharedGenerator();

	Math::Vector<double> *solution = NTGradientAlgorithm::solve(problem);
	delete[] xM;
	return solution;
}


NTGSAAlgorithm::~NTGSAAlgorithm()
{
}
