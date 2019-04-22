#include "pch.h"
#include "NTCGSAAlgorithm.h"
#include <math.h>
#include "LinearSearch.h"
#include "Log.h"

using namespace Math;


NTCGSAAlgorithm::NTCGSAAlgorithm(Math::Vector<double> *initial, double T, double speed, double radius): NTConjugateGradientAlgorithm(initial)
{
	this->TInitial = T;
	this->coolDownSpeed = speed;
	this->radius = radius;
}


NTCGSAAlgorithm::~NTCGSAAlgorithm()
{
}

void NTCGSAAlgorithm::getRandomOffset(double *xM, double *x, int size, double radius) {
	for (int i = 0; i < size; i++) {
		xM[i] = x[i] + r->next() % ((int)(2 * radius * 1e3)) / 1e3 - radius;
	}
}

void NTCGSAAlgorithm::coppyValues(double *x, double *xM, int size) {
	for (int i = 0; i < size; i++) {
		x[i] = xM[i];
	}
}

Math::Vector<double> *NTCGSAAlgorithm::solve(NTGradientProblem *problem) {
	xM = new double[problem->size];
	T = TInitial; 
	r = RandomGenerator::getSharedGenerator();
	Math::Vector<double> *solution = NTConjugateGradientAlgorithm::solve(problem);
	//delete[] xM;
	return solution;
}

void NTCGSAAlgorithm::makeStep(NTGradientProblem *problem) {
	if (T > 0) {
		getRandomOffset(xM, x, size, this->radius);
		double FM = problem->targetFunction(size, xM);
		double F = problem->targetFunction(size, x);
		double P = exp(-abs(FM - F) / T);
		double p = r->next() % 100 * 0.01;
		if (FM < F || p < P) {
			coppyValues(x, xM, size);
		}
		T -= this->coolDownSpeed;
	}
	NTConjugateGradientAlgorithm::makeStep(problem);
}