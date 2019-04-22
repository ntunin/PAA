#pragma once
#include "RandomGenerator.h"
#include "NTGradientAlgorithm.h"

class NTGSAAlgorithm : public NTGradientAlgorithm
{
private:
	double TInitial;
	double T;
	double coolDownSpeed;
	RandomGenerator *r;
	double radius;
	void getRandomOffset(double *x, int size, double radius);
	void coppyValues(double *x, int size);
	double *xM;

public:
	NTGSAAlgorithm(Math::Vector<double> *initial, double T, double speed, double radius);
	~NTGSAAlgorithm();
	Math::Vector<double> *solve(NTGradientProblem *problem);
	void makeStep(NTGradientProblem *problem);
};

