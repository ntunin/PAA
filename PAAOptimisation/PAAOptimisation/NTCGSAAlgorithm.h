#pragma once
#include "NTConjugateGradientAlgorithm.h"
#include "RandomGenerator.h"

class NTCGSAAlgorithm: public NTConjugateGradientAlgorithm
{
private:
	double TInitial;
	double T;
	double coolDownSpeed; 
	RandomGenerator *r;
	double radius;
	void getRandomOffset(double *xM, double *x, int size, double radius);
	void coppyValues(double *x, double *xM, int size);
	double *xM;

public:
	NTCGSAAlgorithm(Math::Vector<double> *initial, double T, double speed, double radius);
	~NTCGSAAlgorithm();
	Math::Vector<double> *solve(NTGradientProblem *problem);
	void makeStep(NTGradientProblem *problem);
};

